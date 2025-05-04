/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:08:45 by vanfossi          #+#    #+#             */
/*   Updated: 2025/05/04 00:02:33 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void create_spc_token(t_token **tokens)
{
	t_token *new_token;

	if(*tokens && ms_strcmp((*tokens)->content," "))
		return;

	new_token = malloc_token();
	new_token->content = " ";
	token_add_back(tokens,new_token);
}

// echo "slt""prout"
// echo "slt"$USER"prout"
// echo "slt$USER"

void token_cat(t_token *t, t_token *n)
{
	t->content = ft_strjoin(t->content, n->content);
	ft_printf(" je suis concatener : %s\n", t->content);
	t->next = n->next;
	free(n);
}

void check_tokens(t_token **tokens)
{
	t_token *t;

	t = *tokens;
	while (t)
	{
		if (t->next && ms_strcmp(t->content, "$") 
			&& !ms_strcmp(t->next->content, " "))
		{
			t->content = "";
			t = t->next->next;
		}
		else if (t->next && ms_strcmp(t->next->content, " "))
		{
			t = t->next->next;
			continue;	
		}
		else if (t->next && is_tok_arg(t->next))
			token_cat(t, t->next);
		else
			t = t->next;
	}
}


t_token	**create_lst_tokens(char *line)
{
	int	in_doubles = 0;
	int	in_singles = 0;
	int	start = 0;
	int	end = 0;
	t_token	**tokens;

	tokens = (t_token **)malloc(sizeof(t_token *));
	*tokens = NULL;
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
		else if (line[end] == ' ' && !in_doubles && !in_singles)
		{
			if (start != end)
				split_token(line, start, end, tokens);
			start = end + 1;
			if(line[end + 1] && line[end + 1] != ' ')
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
