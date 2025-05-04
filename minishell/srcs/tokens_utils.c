/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:15:50 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/24 11:48:10 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void create_token(char *line, int start, int end, t_token **tokens)
{
	t_token *new_token;

	if(end <= start)
		return ;
	new_token = malloc_token();
	new_token->content = ft_substr(line, start, (end-start));
	token_add_back(tokens,new_token);
}


int check_redirection_pipe(char *line)
{
	if(*line == '>' && *(line+1) == '>')
		return (2);
	else if(*line == '<' && *(line+1) == '<')
		return (2);
	else if(*line == '>')
		return (1);
	else if(*line == '<')
		return (1);
	else if(*line == '|')
		return (1);
	else
		return (0);
}

int get_redir_type(t_token *t)
{
	if(ms_strcmp(t->content,"<"))
		return (R_IN);
	else if(ms_strcmp(t->content,">"))
		return (R_OUT);
	else if(ms_strcmp(t->content,">>"))
		return (R_APPEND);
	else if(ms_strcmp(t->content,"<<"))
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

t_token *malloc_token(void)
{
	t_token *new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->type = 0;
	new_token->content = NULL;
	new_token->next = NULL;
	return (new_token);
}

int is_tok_redir(t_token *t)
{
	if(!t->content)
		return (0);
	else if(ms_strcmp(t->content,">"))
		return (1);
	else if (ms_strcmp(t->content,">>"))
		return (1);
	else if (ms_strcmp(t->content,"<"))
		return (1);
	else if (ms_strcmp(t->content,"<<"))
		return (1);
	else
		return (0);
}

int is_tok_arg(t_token *t)
{
	if(!t)
		return (0);
	if(!is_tok_redir(t) && !is_tok_cmd(t) && !is_tok_pipe(t))
		return (1);
	else
		return (0);
}

int is_str_exec(char *t)
{
	char *s;
	int i;

	i = 0;
	if(t)
	{
		s = ft_strtrim(t,"\"\'");
		while(s[i] == ' ')
			i ++;
		while(s[i] == '.')
			i ++;
		if(s[i] == '/')
			return (1);
		else
			return (0);
	}
	return (0);
}
int is_tok_cmd(t_token *t)
{
	int i;
	
	i = 0;
	while(ms_cmdlst()[i])
	{
		if(ms_strcmp(ms_cmdlst()[i],ft_strtrim(t->content,"\'\"")))
			return (1);
		else if(is_str_exec(t->content))
			return (1);
		i ++;
	}
	return (0);
}


int is_tok_pipe(t_token *t)
{
	if(ms_strcmp(t->content,"|"))
		return (1);
	else
		return (0);
}

void	ms_lstdelone(t_token *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}