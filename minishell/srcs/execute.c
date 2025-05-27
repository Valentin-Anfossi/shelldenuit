/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:23:05 by vanfossi          #+#    #+#             */
/*   Updated: 2025/05/27 20:28:40 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_all(t_shell *s, t_job *j)
{}

int	is_builtin(char *cmd)
{
	char	**lstcmd;
	int		i;

	lstcmd = ms_cmdlst();
	i = 0;
	while (lstcmd[i] != NULL)
	{
		if (ms_strcmp(lstcmd[i], cmd))
			return (1);
		i++;
	}
	return (0);
}

int n_jobs(t_job *j)
{
	int n;
	t_job *job;

	n = 1;
	job = j;
	while(job->piped_job)
	{
		n ++;
		job = job->piped_job;	
	}
	return (n);
}

static void	wait_all(t_shell* s, t_job *j)
{
	int		status;
	int		pid;
	int		n;
	t_job	*job;

	n = n_jobs(j);
	job = j;
	while (n--)
	{
		pid = waitpid(0, &status, 0);
		if (pid == gl_pid)
		{
			if (WIFEXITED(status))
				s->exit_code = WEXITSTATUS(status);
		}
		if (job->fd_outfile >= 0)
			close(j->fd_outfile);
		if (job->fd_infile >= 0)
			close(j->fd_infile);
		job = job->piped_job;
	}
}


int	execute_builtin(t_job *j, t_shell *s)
{
	int stdout_tmp;
	
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

void execute_prog(t_job *j, t_shell *s)
{
	int fd;
	char *buffer;
	int	bytes;
	
	if(is_str_cmd(j->cmd))
	select_command(j,s);
	else
	{
		ms_execvp(j->cmd, ms_fix_args(j), s);	
	}
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
		path_absolute(path, j->cmd, s->env); // 
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

void process_child(t_shell *s, t_job *j, int *tuyau)
{
	char *path;

	if(is_builtin(j->cmd))
		execute_builtin(j,s);
	else if(cmd_valid(&path, s, j))
	{
		set_redir(s, j, tuyau);
	}
	else
	{
		execute_prog(j, s);
	}
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
	{
		process_child(s, j, tuyau);
	}
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
		return(execute_builtin(job, s));
	while(job)
	{
		if(pipe(tuyau) == -1)
		return (0);
		execute_fork(s, job, tuyau);
		job = job->piped_job;
	}
	wait_all(s,j);
}


// int	exec(t_shell *s, t_job *j)
// {
	// 	t_job	*tmp;
	// 	int		*pip;
	
	// 	pip = *s->pipefd;
	// 	tmp = j;
	// 	if (tmp && !tmp->piped_job && tmp->cmd
	// 		&& is_builtin(tmp->cmd))
	// 		return (execute_builtin(j, s));
	// 	if (pipe(pip) == -1)
	// 		return (1);
	// 	execute_fork(s, tmp, pip);
	// 	tmp = tmp->piped_job;
// 	while (tmp)
// 	{
// 		if (pipe(pip) == -1)
// 			return (-1);
// 		execute_fork(s, tmp, pip);
// 		tmp = tmp->piped_job;
// 	}
// 	wait_all(s,j);
// 	return (0);
// }

// Seulement la derniere redir est prise en compte mais les autres crees quand meme un fichier vide

/*cree $? des le debut a 0
Modifier a chaque fin de fork par le execve/execvp*/