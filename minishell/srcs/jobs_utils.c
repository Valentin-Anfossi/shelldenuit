/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:28:18 by vanfossi          #+#    #+#             */
/*   Updated: 2025/05/31 04:17:10 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_job	*malloc_job(int lestoks)
{
	t_job *job;
	
	job = (t_job *)ft_calloc(1,sizeof(t_job));
	job->args = (char **)ft_calloc(lestoks,sizeof(char *));
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


//Prints errors, return 1 if an error is present
int check_jobs(t_job *jobs, t_shell *s)
{
	t_job *j;
	int re;
	int i;

	i = 0;
	re = 0;
	if(!jobs)
		return (1);
	j = jobs;
	while(j)
	{
		if (!j->cmd && j->args[i])
		{
			while(ms_strcmp(j->args[i], " "))
				i++;
			j->cmd = j->args[i];
			if(!re)
				ft_printf("%s: command not found\n",ft_strtrim(jobs->args[i],"\"\'"));
			re = 1;
		}
		else if(j->error == ERR_NEWLINE)
		{
			if (!re)
				ft_printf("syntax error near unexpected token `newline'\n");
			re = 1;
		}
		j = j->piped_job;
		i = 0;
	}
	//re = check_redirs(jobs);
	return (re);
}

//Free all the jurbs
void	free_jobs(t_job *jobs)
{
	t_redir	*r;
	t_job	*j;
	int		i;

	while (jobs)
	{
		i = 0;
		// if (jobs->cmd)
		// 	free(jobs->cmd);

		while (jobs->redir)
		{
			r = jobs->redir->next;
			free(jobs->redir);
			jobs->redir = r;
		}
		while (jobs->args[i] != NULL)
		{
			free(jobs->args[i]);
			i ++;
		}
		free(jobs->args);
		j = jobs->piped_job;
		free(jobs);
		jobs = j;
	}
}
