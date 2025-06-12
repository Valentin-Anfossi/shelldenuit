/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:08:45 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/12 23:09:43 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_spc_token(t_token **tokens)
{
	t_token	*new_token;

	if (*tokens && ms_strcmp((*tokens)->content, " "))
		return ;

	new_token = malloc_token();
	new_token->content = ft_strdup(" ");
	token_add_back(tokens, new_token);
}

// echo "slt""prout"
// echo "slt"$USER"prout"
// echo "slt$USER"

void	token_cat(t_token *t, t_token *n)
{
	char *tmp;
	
	tmp = ft_strjoin(t->content, n->content);
	free(t->content);
	t->content = tmp;
	t->next = n->next;
	free(n);
}

void	check_tokens(t_token **tokens)
{
	t_token	*t;

	t = *tokens;
	while (t)
	{
		if (t->next && ms_strcmp(t->content, "$") && t->type != DBQ
			&& !ms_strcmp(t->next->content, " "))
		{
			free(t->content);
			t->content = ft_strdup("");
			t = t->next->next;
		}
		else if (t->next && ms_strcmp(t->next->content, " "))
		{
			t = t->next->next;
			continue ;
		}
		else if(t->type >= OUT && t->type <= HER)
		{
			while(t->next && t->next->type == 0)
				t = t->next;
			if(t->next && (t->next->type == ARG || t->next->type == DBQ || t->next->type == SQ))
				t = t->next;
			if(!t->next || is_tok_redir(t->next))
				break;
		}
		else if (t->next && is_tok_arg(t->next) && t->type != 0 && t->type != PIP)
			token_cat(t, t->next);
		else
			t = t->next;
	}
	t = *tokens;
}

t_token	*create_lst_tokens(char *line)
{
	int		in_doubles = 0;
	int		in_singles = 0;
	int		start = 0;
	int		end = 0;
	t_token	*tokens;

	tokens = (t_token *)malloc(sizeof(t_token *));
	tokens = NULL;
	while (line[start] && ft_isspace(line[start]))
		start ++;
	end = start;
	while (line[end])
	{
		if (line[end] == '"' && !in_singles)
		{
			if (in_doubles)
			{
				create_token(line, start, end + 1, tokens);
				start = end + 1;
				in_doubles = 0;
			}
			else if (ft_strchr(&line[end + 1], '"'))
			{
				split_token(line, start, end, tokens);
				start = end;
				in_doubles = 1;
			}
		}
		else if (line[end] == '\'' && !in_doubles)
		{
			if (in_singles)
			{
				create_token(line, start, end + 1, tokens);
				start = end + 1;
				in_singles = 0;
			}
			else if (ft_strchr(&line[end + 1], '\''))
			{
				split_token(line, start, end, tokens);
				start = end;
				in_singles = 1;
			}
		}
		else if (ft_isspace(line[end]) && !in_doubles && !in_singles)
		{
			if (start != end)
				split_token(line, start, end, tokens);
			start = end + 1;
			if (line[end + 1] && !ft_isspace(line[end + 1]))
				create_spc_token(tokens);
		}
		end++;
	}
	if (start < end)
		split_token(line, start, end, tokens);
	return (tokens);
}

void	split_token(char *line, int start, int end, t_token **tokens)
{
	int	i;

	i = 0;
	i = start;
	while (i <= end)
	{
		if (check_redirection_pipe(&line[i]))
		{
			create_token(line, start, i, tokens);
			create_token(line, i, i + check_redirection_pipe(&line[i]), tokens);
			i += (check_redirection_pipe(&line[i]));
			start = i;
		}
		else if (i == end)
		{
			create_token(line, start, end, tokens);
			i++;
		}
		else
			i ++;
	}
}
int	is_tok_quoted(t_token *tok)
{
	if (tok->content[0] == '\''
		&& tok->content[ft_strlen(tok->content)] == '\'')
		return (1);
	else
		return (0);
}

int	verif_tokens(t_token *token)
{
	t_token *t;

	t = token;
	printf("veriftokens\n");
	while(t)
	{
		if(is_tok_redir(t))
		{
			while(t->next && t->next->type == 0)
				t = t->next;
			if(t->next && (!is_tok_arg(t->next) || is_tok_redir(t->next)))
			{
				printf("Minishell: syntax error near unexpected token '%s'\n",t->next->content);
				return (1);
			}
			else if (!t->next)
			{
				printf("Minishell: syntax error near unexpected token `newline'\n");
				return (1);
			}
		}
		t = t->next;
	}
	return (0);
}

int	tokens_start(t_token **t, t_shell *s)
{
	if (!*t)
	{
		return (1);
	}
	if (!(*t)->next && (ms_strcmp((*t)->content,"!") || ms_strcmp((*t)->content,":")))
		return (1);
	typing_tokens(t);
	check_env(t, s);
	debug_print_tokens(t);
	check_tokens(t);
	return (verif_tokens(*t));
	return (0);
}

t_tokenlst *ms_create_tlst(char *line, t_token *t)
{
	t_tokenlst *tlst;

	tlst = (t_tokenlst *)malloc(sizeof(t_tokenlst));
	tlst->line = line;
	tlst->start = 0;
	tlst->end = 0;
	tlst->in_doubles = 0;
	tlst->in_singles = 0;
	tlst->t = t;

	return (tlst);
}

void ms_lst_doubles(t_tokenlst *tlst)
{
	if (tlst->in_doubles)
	{
		create_token(tlst->line, tlst->start,tlst->end + 1, tlst->t);
		tlst->start = tlst->end + 1;
		tlst->in_doubles = 0;
	}
	else if (ft_strchr(&tlst->line[tlst->end + 1], '"'))
	{
		split_token(tlst->line, tlst->start, tlst->end, tlst->t);
		tlst->start = tlst->end;
		tlst->in_doubles = 1;
	}
}

void ms_lst_singles(t_tokenlst *tlst)
{
	if (tlst->in_singles)
	{
		create_token(tlst->line, tlst->start, tlst->end + 1, tlst->t);
		tlst->start = tlst->end + 1;
		tlst->in_singles = 0;
	}
	else if (ft_strchr(&tlst->line[tlst->end + 1], '\''))
	{
		split_token(tlst->line, tlst->start, tlst->end, tlst->tokens);
		tlst->start = tlst->end;
		tlst->in_singles = 1;
	}	
}

t_token	*ms_lst_tokens(char *line)
{
	t_tokenlst *tlst;
	t_token	*tokens;
	int		in_doubles = 0;
	int		in_singles = 0;
	int		start = 0;
	int		end = 0;

	tokens = (t_token *)malloc(sizeof(t_token *));
	tlst = ms_create_tlst(line,tokens);
	while (line[tlst->start] && ft_isspace(line[tlst->start]))
		tlst->start ++;
	tlst->end = tlst->start;
	while (line[tlst->end])
	{
		if (line[tlst->end] == '"' && !tlst->in_singles)
			ms_lst_doubles(tlst);
		else if (line[end] == '\'' && !in_doubles)
			ms_lst_singles(tlst);
		else if (ft_isspace(line[end]) && !in_doubles && !in_singles)
		{
			if (start != end)
				split_token(line, start, end, tokens);
			start = end + 1;
			if (line[end + 1] && !ft_isspace(line[end + 1]))
				create_spc_token(tokens);
		}
		end++;
	}
	if (start < end)
		split_token(line, start, end, tokens);
	return (tokens);
}
