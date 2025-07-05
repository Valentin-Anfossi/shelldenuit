/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:12:48 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/05 18:26:48 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ms_execute_jobs(t_job *job, t_shell *sh)
{
	t_exec	*ex;
	int		i;

	ex = ms_exec_create(job, sh);
	if (ex->n_jobs == 1 && is_builtin(job->cmd))
		return (ms_execute_single(job, sh, ex));
	else
	{
		i = 0;
		while (i < ex->n_jobs)
		{
			ex->child_pids[i] = fork();
			if (ex->child_pids[i] == 0)
				exit(ms_execute_child(job, ex, i));
			job = job->piped_job;
			i++;
		}
		ms_pips_closeall(ex->pipes, ex->n_jobs - 1);
		ms_waitjobs(ex, i);
	}
	ms_free_ex(ex);
	handle_signals();
	return (0);
}

void	ms_waitjobs(t_exec *ex, int i)
{
	int	h;
	int	status;

	h = 0;
	while (h < i)
	{
		waitpid(ex->child_pids[h], &status, WUNTRACED);
		if (WIFSIGNALED(status))
		{
			if ((128 + WTERMSIG(status)) == 131 && h == (i -1))
				ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
			if ((128 + WTERMSIG(status)) == 130 && h == (i -1))
				ft_putstr_fd("\n", STDERR_FILENO);
			g_exitcode = 128 + WTERMSIG(status);
		}
		else if (status >= 256)
			g_exitcode = status / 256;
		else
			g_exitcode = status;
		h ++;
	}
}

void	ms_free_ex(t_exec *ex)
{
	free(ex->pipes);
	free(ex->child_pids);
	free(ex);
}

int	ms_execute_child(t_job *j, t_exec *ex, int i)
{
	int	code;

	code = 0;
	handle_signals_child();
	if (ms_execute_redir(j, ex, i))
		return (1);
	ms_pips_close(ex->pipes, ex->n_jobs - 1, i);
	if (is_builtin(j->cmd))
		return (select_command(j, ex->shell));
	else
	{
		code = ms_execvp(j->cmd, j->args, ex->shell);
		if (code)
			code = err_cmd_nfound(j->cmd);
		return (code);
	}
}

t_exec	*ms_exec_create(t_job *job, t_shell *shell)
{
	t_exec	*ex;

	ex = (t_exec *)malloc(sizeof(t_exec));
	ex->n_jobs = ms_count_jobs(job);
	ex->pipes = ms_create_pipes(ex->n_jobs - 1);
	ex->child_pids = (pid_t *)malloc(ex->n_jobs * sizeof(pid_t));
	ex->job = job;
	ex->shell = shell;
	return (ex);
}
