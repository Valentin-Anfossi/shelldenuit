/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:28:18 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/14 10:59:58 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_job(t_job *j, t_token **tok)
{
	t_token *t;

	t = *tok;

	while (t)
	{
		if (is_tok_redir(t))
			t = add_to_job_redir(t, &j);
		else if (!j->cmd)
		{
			add_to_job_cmd(t, j);
			t = add_to_job_arg(t, j);
		}
		else if (is_tok_pipe(t))
		{
			t = t->next;
			j ->piped_job = create_job(&t);
			break ;
		}
		else
			t = add_to_job_arg(t, &j);
	}
	if(!j->cmd)
	{
		j->cmd = ft_strdup("");
		return (1);
	}
	return (0);
}

t_job	*create_job(int toks)
{
	t_job	*job;

	job = (t_job *)ft_calloc(1, sizeof(t_job));
	job->cmd = (char *)malloc(sizeof(char *));
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

//Prints errors, return 1 if an error is present
// int	check_jobs(t_job *jobs)
// {
// 	t_job	*j;
// 	int		re;
// 	int		i;

// 	i = 0;
// 	re = 0;
// 	if (!jobs)
// 		return (1);
// 	j = jobs;
// 	while (j)
// 	{
// 		if (!j->cmd && j->args[i])
// 		{
// 			while (ms_strcmp(j->args[i], " "))
// 				i++;
// 			j->cmd = j->args[i];
// 			if (!re)
// 				ft_printf("%s: command not found\n", ft_strtrim(jobs->args[i], "\"\'"));
// 			re = 1;
// 		}
// 		else if (j->error == ERR_NEWLINE)
// 		{
// 			if (!re)
// 				ft_printf("syntax error near unexpected token `newline'\n");
// 			re = 1;
// 		}
// 		j = j->piped_job;
// 		i = 0;
// 	}
// 	//re = check_redirs(jobs);
// 	return (re);
// }

//Free all the jurbs
void	free_jobs(t_job *jobs)
{
	t_redir	*r;
	t_job	*j;
	int		i;

	while (jobs)
	{
		i = 0;
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
		if(jobs->cmd)
			free(jobs->cmd);
		free(jobs->args);
		j = jobs->piped_job;
		free(jobs);
		jobs = j;
	}
	if(jobs)
		free(jobs);
}
