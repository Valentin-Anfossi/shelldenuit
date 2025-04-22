/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:11:05 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/22 05:28:57 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_job	*create_job(t_token **tokens, t_job **jobs)
{
	t_job	*new_job;
    t_token *t;
	int		i;
	
    t = *tokens;
	i = 0;
	new_job = malloc_job();
	while (t->type == SPC && t->next)
		t = t->next;
    new_job->cmd = ft_strdup(ft_strtrim(t->content, "\"\'"));
	if (!check_for_commands(t->content))
	new_job->error = 1;
	while(t->content)
	{
		if (!t->next)
		break;
		t = t->next;
		if (t->type == ARG && ms_strcmp(t->content, "|") == 0)
		break ;
		else if (t->type == ARG || t->type == QUO_D || t->type == QUO_S)
		{
			new_job->args[i] = ft_strdup(t->content);
			i++;
		}
		else if (t->type != SPC)
		new_job->redir->type = t->type;
	}
	if (ms_strcmp(t->content, "|") == 0)
	{
		t = t->next;
		new_job->piped_job = create_job(&t, jobs);
	}
	new_job->args[i] = NULL;
	return (new_job);
}

t_job	**create_lst_job(t_token **tokens)
{
	t_job **jobs;
	
	jobs = (t_job **)malloc(sizeof(t_job *));
	*jobs = create_job(tokens, jobs);
	return (jobs);
}