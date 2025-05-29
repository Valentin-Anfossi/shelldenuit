/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:23:05 by vanfossi          #+#    #+#             */
/*   Updated: 2025/05/29 01:36:24 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_job *j, t_shell *s, int *tuyau)
{
	int stdout_tmp;
	
	close(tuyau[0]);
	if(j->fd_outfile < 0 && j->piped_job)
		j->fd_outfile = tuyau[1];
	else
		close(tuyau[1]);
	stdout_tmp = -1;
	if (j->fd_outfile >= 0)
	{
		stdout_tmp = dup(STDOUT_FILENO);
		dup2(j->fd_outfile,STDOUT_FILENO);
	}
	select_command(j, s);
	if (j->fd_outfile >= 0)
	{
		dup2(stdout_tmp, STDOUT_FILENO);
		close(stdout_tmp);
		close(j->fd_outfile);
	}
	return (1);
}

void path_absolute(char **path, t_shell *s, t_job *j)
{
	*path = ft_strdup(j->cmd);
	if(!(*path))
	{
		s->exit_code = 999; // PAR EX
		exit_all(s, j);//DOIT PRENDRE ERROR MSG (EX MALLOC ERROR)
	}
	if(access((*path), F_OK))
	{
		printf("%s : command not found\n",path);
		free(*path);
		*path = NULL;
	}
}

char *find_cmd(char *path, t_shell *s, t_job *j)
{
	char **dirs;
	char *path_env;
	int i;
	
	i = 0;
	path_env = ms_getenv("PATH",s);
	if (!path_env)
	{
		printf("PATH doesn't exist.");
		return (NULL);
	}
	dirs = ft_split(path, ':');
	while(dirs[i])
	{
		path = ft_strjoin(dirs[i],ft_strjoin("/", j->cmd));
		if(is_executable(path))
			return(path);
		i ++;
	}
	return(NULL);
}

int cmd_valid(char **path, t_shell *s, t_job *j)
{
	if(!ft_strchr(j->cmd,'/')) //SI CEST UNE COMMANDE SANS /
		*path = find_cmd(path, s, j);
	else //SI CEST UN CHEMIN ABSOLU "./dossier/executable"
		path_absolute(path, s, j); // 
	if(!(*path))
	{
		s->exit_code = 127;
		return (0);
	}
	if (access((*path), X_OK))
	{
		perror(*path);
		free((*path));
		(*path) = NULL;
		s->exit_code = 126;
		return (0);
	}
	if (is_folder(*path))
	{
		write(2, (*path), ft_strlen(*path));
		write(2, " : command not found\n", 21);
		return (0);
	}
	return (1);
}

void set_redir(t_shell *s, t_job *j, int *tuyau)
{
	close(tuyau[0]);
	if(j->fd_infile >= 0)
	{
		dup2(j->fd_infile, 0);
		close(j->fd_infile);
	}
	if(j->fd_outfile >= 0)
	{
		dup2(j->fd_outfile, 1);
		close(j->fd_outfile);
	}
	else if(j->piped_job)
		dup2(tuyau[1], 1);
	close(tuyau[1]);
}

void process_child(t_shell *s, t_job *j, int *tuyau)
{
	char *path;

	if(is_builtin(j->cmd))
		execute_builtin(j,s,tuyau);
	else if(cmd_valid(&path, s, j))
	{
		set_redir(s, j, tuyau);
		rl_clear_history();
		signal(SIGQUIT, SIG_DFL);
		execve(path, j->args, s->env);
	}
	// if (path)
	// 	free(path);
	exit_all(s,j);
}

void	process_parent(t_shell *s, t_job *j, int *tuyau)
{
	close(tuyau[1]);
	if (j->fd_infile >= 0)
		close(j->fd_infile);
	if (j->fd_infile == -2)
		j->fd_infile = tuyau[0];
	if (j->piped_job && j->piped_job->fd_infile == -2)
		j->piped_job->fd_infile = tuyau[0];
	else
		close(tuyau[0]);
}

void execute_fork(t_shell *s, t_job *j, int *tuyau)
{
	gl_pid = fork();
	if(gl_pid < 0)
		exit_all(s, j);
	else if (gl_pid == 0)
		process_child(s, j, tuyau);
	else
		process_parent(s, j, tuyau);
}

int execute_jobs(t_job *j, t_shell *s)
{
	t_job *job;
	int *tuyau;
	
	tuyau = s->tuyau;
	job = j;
	if(!job->piped_job && is_str_cmd(job->cmd))
		return(execute_builtin(job, s, tuyau));
	if(pipe(tuyau) == -1)
		return (0);
	execute_fork(s,job,tuyau);
	job = job->piped_job;
	while(job)
	{
		printf("job !");
		if(pipe(tuyau) == -1)
			return (0);
		execute_fork(s, job, tuyau);
		// if(!job->piped_job)
		// 	break;
		job = job->piped_job;
	}
	wait_all(s,j);
	return (1);
}