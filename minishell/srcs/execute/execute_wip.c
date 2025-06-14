/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_wip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:12:48 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/14 23:27:31 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_execute_jobs(t_job *job, t_shell *sh)
{
	t_exec *ex;
	int i;

	i = 0;
	ex = ms_exec_create(job,sh);
	if(ex->n_jobs == 1 && is_builtin(job->cmd))
		return (ms_execute_single(job,sh,ex));
	while(i < ex->n_jobs)
	{
		ex->pid = fork();
		if(pid == 0)
		{
			exit(ms_execute_child(j,sh,ex,i);

			
			
		}
	}
}

int ms_execute_child(t_job *j, t_shell *sh, t_exec *ex, int i)
{
	handle_signals_child();
	if(ms_execute_redir(j,sh))
		return (g_exitcode);
	ms_pips_close(ex->pipes,j,i);
}

t_exec *ms_exec_create(t_job *job, t_shell *shell)
{
	t_exec *ex;
	
	ex = malloc(sizeof(t_exec));
	ex->n_jobs = ms_count_jobs(job);
	ex->pipes = ms_create_pipes(ex->n_jobs - 1);
	ex->child_pids = (pid_t *)malloc(ex->n_jobs * sizeof(pid_t));
	ex->job = job;
	ex->shell = shell;
	return (ex);
}

int ms_count_jobs(t_job *job)
{
	int n;
	
	n = 0;
	if(!job)
		return (n);
	while(job)
	{
		n ++;
		job = job->piped_job;
	}
	return (n);
}
