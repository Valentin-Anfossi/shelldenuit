/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:28:18 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/05 14:53:07 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_job	*malloc_job(int toks)
{
	t_job	*job;

	job = (t_job *)ft_calloc(1, sizeof(t_job));
	job->args = (char **)ft_calloc(toks, sizeof(char *));
	*job->args = NULL;
	job->redir = NULL;
	job->cmd = NULL;
	job->pid = 0;
	job->fd_infile = -1;
	job->fd_outfile = -1;
	job->error = 0;
	job->piped_job = NULL;
	return (job);
}

t_job	*free_jobs_helper(t_job *jobs)
{
	int		i;
	t_redir	*r;
	t_job	*j;

	i = 0;
	while (jobs->redir)
	{
		r = jobs->redir->next;
		free(jobs->redir->target);
		free(jobs->redir);
		jobs->redir = r;
	}
	while (jobs->args[i] != NULL)
	{
		free(jobs->args[i]);
		i ++;
	}
	if (jobs->cmd)
		free(jobs->cmd);
	free(jobs->args);
	j = jobs->piped_job;
	free(jobs);
	return (j);
}

//Free all the jurbs
void	free_jobs(t_job *jobs)
{
	while (jobs)
	{
		jobs = free_jobs_helper(jobs);
	}
	if (jobs)
		free(jobs);
}
