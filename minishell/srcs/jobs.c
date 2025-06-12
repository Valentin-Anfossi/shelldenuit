/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:11:05 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/12 16:23:23 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*add_to_job_redir(t_token *t, t_job *j)
{
	t_redir	*new_redir;
	t_redir	*cur_redir;

	new_redir = (t_redir *)ft_calloc(sizeof(t_redir), 1);
	new_redir->type = get_redir_type(t);
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
		while (t->next->type == 0)
			t = t->next;
		new_redir->target = ft_strdup(t->next->content);
		new_redir->next = NULL;
		t = t->next->next;
		return (t);
	}
	else if (!j->error)
		j->error = ERR_NEWLINE;
	return (t);
}

t_token	*add_to_job_cmd(t_token *t, t_job *j)
{
	j->cmd = ft_strtrim(t->content, "\'\"");
	t = t->next;
	return (t);
}

t_token	*add_to_job_arg(t_token *t, t_job *j)
{
	int	i;

	i = 0;
	if (!j->args[0])
	{
		j->args[0] = ft_strdup(t->content);
		j->args[1] = NULL;
		return (t->next);
	}
	while (j->args[i])
		i ++;
	j->args[i] = ft_strdup(t->content);
	j->args[i + 1] = NULL;
	return (t->next);
}
void add_next_tok(t_token *t, t_job *j)
{
	if (t->next)
		j->args[0] = t->next->content;
}

t_job	*create_job(t_token **tokens)
{
	t_token	*t;
	t_job	*j;

	j = malloc_job(combiendetoks(tokens)+1);
	t = *tokens;
	while (ms_strcmp(t->content, " "))
		t = t->next; // Faut skip les spaces au debut de chaque job
	while (t)
	{
		if (is_tok_redir(t))
		{
			if (is_tok_arg(t->next)) // IS_TOK_ARG probleme car check is_tok_cmd fait foirer (path et cmd commencent par ./)
				t = add_to_job_redir(t, j);
			else if(t->next)
			{
				// add_next_tok(t, j)
				printf("Minishell: syntax error near unexpected token'%s'",t->next->content);
				// printf("error token suivant\n");
				break ;
			}
		}
		else if (!j->cmd && ft_strlen(t->content) > 0 && t->type != SPC)
		{
			add_to_job_cmd(t, j);
			t = add_to_job_arg(t, j); // NEEDED FOR EXCVE
			while (t && t->type == SPC)
				t = t->next;
		}
		else if (is_tok_pipe(t))
		{
			t = t->next;
			j ->piped_job = create_job(&t);
			break ;
		}
		else if (t->type != SPC && ft_strlen(t->content) > 0) //REMOVED SPACES (FRANCHEMENT JE SAIS PLUS POURQUOI MAIS CA VA NOUS FAIRE CHIER APRES)
			t = add_to_job_arg(t, j);
		else
			t = t->next;
	}
	if(!j->cmd)
		j->cmd = ft_strdup("");
	return (j);
}
