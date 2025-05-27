/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:23:05 by vanfossi          #+#    #+#             */
/*   Updated: 2025/05/24 09:16:15 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_all(t_shell *s, t_job *j)
{}
void	wait_all()
{
	int	status;
	
	while (wait(&status) > 0);
}

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

void process_child(t_shell *s, t_job *j, int *tuyau)
{
	if(is_builtin(j->cmd))
		execute_builtin(j,s);
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

int execute_jobs(t_job *jobs, t_shell *shell)
{
	t_job *j;
	int *tuyau;
	
	
	j = jobs;
	if(!j->piped_job && is_str_cmd(j->cmd))
		return(execute_builtin(j, shell));
	while(j)
	{
		if(pipe(tuyau) == -1)
			return (0);
		execute_fork(shell, j, tuyau);
		j = j->piped_job;
	}
}

int	exec(t_shell *s, t_job *j)
{
	t_job	*tmp;
	int		*pip;

	pip = *s->pipefd;
	tmp = j;
	if (tmp && !tmp->piped_job && tmp->cmd
		&& is_builtin(tmp->cmd))
		return (execute_builtin(j, s));
	if (pipe(pip) == -1)
		return (1);
	execute_fork(s, tmp, pip);
	tmp = tmp->piped_job;
	while (tmp)
	{
		if (pipe(pip) == -1)
			return (-1);
		execute_fork(s, tmp, pip);
		tmp = tmp->piped_job;
	}
	wait_all(s);
	return (0);
}

// Seulement la derniere redir est prise en compte mais les autres crees quand meme un fichier vide






/*cree $? des le debut a 0
Modifier a chaque fin de fork par le execve/execvp*/