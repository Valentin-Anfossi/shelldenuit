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

void exit_all(t_shell *s, t_job *j)
{}

int execute_builtin(t_job *j, t_shell *s)
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


void execute_fork(t_job *j, t_shell *s, int *tuyau)
{
	gl_pid = fork();
	if(gl_pid < 0)
	exit_all(s);
	else if (!gl_pid)
	{
		process_child(j,s,tuyau);
	}
	else
	process_parent(j,s,tuyau);
}

void process_child(t_job *j, t_shell *s, int *tuyau)
{
	if(is_str_cmd(j->cmd))
	execute_builtin(j,s);
	else
	{
		
	}
}

static void	process_parent(t_shell *s, t_job *s, int *tuyau)
{
	close(pip[1]);
	if (cmd->infile >= 0)
	close(cmd->infile);
	if (cmd->infile == -2)
	cmd->infile = pip[0];
	if (cmd->next != data->cmd && cmd->next->infile == -2)
	cmd->next->infile = pip[0];
	else
	close(pip[0]);
}

int execute_jobs(t_job *jobs, t_shell *shell)
{
	t_job *j;
	int *tuyau;
	
	
	j = jobs;
	if(!j->piped_job && is_str_cmd(j->cmd))
		return(execute_builtin(j,shell));
	while(j)
	{
		if(pipe(tuyau) == -1)
			return (0);
		execute_fork(j,shell,tuyau);
		j = j->piped_job;
	}
}

bool	exec(t_data *data)
{
	t_cmd	*tmp;
	int		*pip;

	pip = data->pip;
	tmp = data->cmd;
	if (tmp && tmp->skip_cmd == false && tmp->next == tmp && tmp->cmd_param[0] \
		&& is_builtin(tmp->cmd_param[0]))
		return (launch_builtin(data, tmp));
	if (pipe(pip) == -1)
		return (false);
	exec_cmd(data, tmp, pip);
	tmp = tmp->next;
	while (tmp != data->cmd)
	{
		if (pipe(pip) == -1)
			return (-1);
		exec_cmd(data, tmp, pip);
		tmp = tmp->next;
	}
	wait_all(data);
	return (true);
}

// Seulement la derniere redir est prise en compte mais les autres crees quand meme un fichier vide
void execute_prog(t_job *j, t_shell *s)
{
	int fd;
	char *buffer;
	int	bytes;

	if(is_str_cmd(j->cmd))
		select_command(j,s);
	else
	{
		ms_execvp(j->cmd,ms_fix_args(j),s);	
	}
}






/*cree $? des le debut a 0
Modifier a chaque fin de fork par le execve/execvp*/