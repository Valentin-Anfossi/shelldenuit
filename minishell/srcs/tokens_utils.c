/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:15:50 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/10 14:59:01 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_token(char *line, int start, int end, t_token **tokens)
{
	t_token	*new_token;

	if (end <= start)
		return ;
	new_token = malloc_token();
	new_token->content = ft_substr(line, start, (end - start));
	token_add_back(tokens, new_token);
}


int	check_redirection_pipe(char *line)
{
	if (*line == '>' && *(line + 1) == '>')
		return (2);
	else if (*line == '<' && *(line + 1) == '<')
		return (2);
	else if (*line == '>')
		return (1);
	else if (*line == '<')
		return (1);
	else if (*line == '|')
		return (1);
	else
		return (0);
}

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

//Add token to the back of lst
void	token_add_back(t_token **lst, t_token *token)
{
	t_token	*last;

	if (!lst || !token)
		return ;
	if (*lst == 0)
		*lst = token;
	else
	{
		last = token_last(*lst);
		last->next = token;
	}
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
