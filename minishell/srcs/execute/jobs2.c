/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:54:43 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/07 21:46:10 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_job	*create_job(t_token **tokens)
{
	t_token	*t;
	t_job	*j;

	j = malloc_job(combiendetoks(tokens)+1);
	t = *tokens;
	while (t && ms_strcmp(t->content, " "))
	{
		t = t->next;
	}
	while (t)
	{
		t = create_job_helper(t, j);
	}
	if (!j->cmd)
		j->cmd = ft_strdup("");
	return (j);
}

t_token	*create_job_helper(t_token *t, t_job *j)
{
	if (is_tok_redir(t))
	{
		if (is_tok_arg(t->next))
			t = add_to_job_redir(t, j);
	}
	else if (!j->cmd && ft_strlen(t->content) > 0 && t->type != SPC)
	{
		add_to_job_cmd(t, j);
		t = add_to_job_arg(t, j);
		while (t && t->type == SPC)
			t = t->next;
	}
	else if (is_tok_pipe(t))
	{
		t = t->next;
		j ->piped_job = create_job(&t);
		return (NULL);
	}
	else if (t->type != SPC && ft_strlen(t->content) > 0)
		t = add_to_job_arg(t, j);
	else
		t = t->next;
	return (t);
}
