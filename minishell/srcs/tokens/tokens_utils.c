/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:15:50 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/13 11:02:40 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	get_redir_type(t_token *t)
{
	if (ms_strcmp(t->content, "<"))
		return (R_IN);
	else if (ms_strcmp(t->content, ">"))
		return (R_OUT);
	else if (ms_strcmp(t->content, ">>"))
		return (R_APPEND);
	else if (ms_strcmp(t->content, "<<"))
		return (R_HEREDOC);
	else
		return (0);
}

//Return last token from lst
t_token	*token_last(t_token *lst)
{
	t_token	*list;

	if (!lst)
		return (0);
	list = lst;
	while (list->next)
		list = list->next;
	return (list);
}

t_token	*malloc_token(void)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->type = 0;
	new_token->content = NULL;
	new_token->next = NULL;
	return (new_token);
}

void	ms_lstdelone(t_token *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}

void typing_tokens(t_token **tokens)
{
	t_token *t;

	t = *tokens;
	while(t)
	{
		if (ms_strcmp(t->content, " "))
			t->type = SPC;
		else if (t->content[0] == '"')
			t->type = DBQ;
		else if (t->content[0] == '\'')
			t->type = SQ;
		else if (ms_strcmp(t->content, ">"))
			t->type = OUT;
		else if (ms_strcmp(t->content, "<"))
			t->type = IN;
		else if (ms_strcmp(t->content, ">>"))
			t->type = APP;
		else if (ms_strcmp(t->content, "<<"))
			t->type = HER;
		else if (ms_strcmp(t->content, "|"))
			t->type = PIP;
		else
			t->type = ARG;
	t = t->next;
	}
}
