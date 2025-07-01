/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:11:05 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/12 19:26:23 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*add_to_job_redir(t_token *t, t_job *j)
{
	t_redir	*new_redir;
	t_redir	*cur_redir;

	new_redir = (t_redir *)ft_calloc(sizeof(t_redir), 1);
	new_redir->type = t->type;
	if (!j->redir)
		j->redir = new_redir;
	else
	{
		cur_redir = j->redir;
		while (cur_redir->next)
			cur_redir = cur_redir->next;
		cur_redir->next = new_redir;
	}
	if (t->next)
	{
		new_redir->target = ft_strdup(t->next->content);
		new_redir->next = NULL;
		t = t->next->next;
		return (t);
	}
	return (t);
}

void	*add_to_job_cmd(t_token *t, t_job *j)
{
	j->cmd = t->content;
}

t_token	*add_to_job_arg(t_token *t, t_job *j)
{
	int	i;

	if (!t)
		return (t);
	i = 0;
	if (!j->args[0])
	{
		j->args[0] = ft_strdup(t->content);
		j->args[1] = NULL;
		return (t->next);
	}
	while (j->args[i] && ft_strlen(j->args[i]) > 0)
		i++;
	j->args[i] = ft_strdup(t->content);
	j->args[i + 1] = NULL;
	return (t->next);
}

void add_next_tok(t_token *t, t_job *j)
{
	if (t->next)
		j->args[0] = t->next->content;
}

t_job	*ms_job(t_token **tokens)
{
	t_token	*t;
	t_job	*j;

	j = create_job(job_arg_count(tokens)+1);
	if (!set_job(j, tokens));
		return(NULL);
	t = *tokens;
	while (t)
	{
		if (is_tok_redir(t))
			t = add_to_job_redir(t, j);
		else if (!j->cmd)
		{
			t = add_to_job_cmd(t, j);
			t = add_to_job_arg(t, j);
		}
		else if (is_tok_pipe(t))
		{
			t = t->next;
			j ->piped_job = ms_job(&t);
			break ;
		}
		else
			t = add_to_job_arg(t, j);
	}
	if(!j->cmd)
		j->cmd = ft_strdup("");
	return (j);
}
 