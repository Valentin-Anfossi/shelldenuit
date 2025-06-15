/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_wip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:12:48 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/15 03:08:23 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		if(ex->pid == 0)
		{
			handle_signals_child();
			exit(ms_execute_child(job, ex, i));
			
			
			
		}
		job = job->piped_job;
		i ++;
	}
}

int ms_execute_child(t_job *j, t_exec *ex, int i)
{
	ms_pips_close(ex->pipes,ex->n_jobs,i);

	if(ms_execute_redir(j,ex->shell, i))
		return (g_exitcode);
	if(is_builtin(j->cmd))
		return(select_command(j,ex->shell));
	else
		return(ms_execvp(j->cmd, j->args, ex->shell));
}

void ms_pips_close(int(*pipes)[2], int n, int j)
{
	int i;

	i = 0;
	while(i < n)
	{
		if(i != j-1)
			close(pipes[i][0]);
		if(i != j)
			close(pipes[i][1]);
		i ++;
	}	
}

int ms_execute_redir(t_job *j, t_exec *ex, int i)
{
	t_redir *r;


	
	if (i > 0)
		dup2(ex->pipes[i - 1][0], STDIN_FILENO);
	if (i < (ex->n_jobs - 1))
		dup2(ex->pipes[i][1], STDOUT_FILENO);
}

t_exec *ms_exec_create(t_job *job, t_shell *shell)
{
	t_exec *ex;
	
	ex = (t_exec *)malloc(sizeof(t_exec));
	ex->n_jobs = ms_count_jobs(job);
	ex->pipes = ms_create_pipes(ex->n_jobs - 1);
	ex->child_pids = (pid_t *)malloc(ex->n_jobs * sizeof(pid_t));
	ex->job = job;
	ex->shell = shell;
	return (ex);
}
int (*ms_create_pipes(int n))[2]
{
	int (*pipes)[2];
	
	pipes = (int (*)[2])malloc(n * sizeof(int [2]));
	if(!pipes)
		return (NULL);
	return (pipes);
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
