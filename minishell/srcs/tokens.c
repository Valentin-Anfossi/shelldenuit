/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:08:45 by vanfossi          #+#    #+#             */
/*   Updated: 2025/05/03 23:13:30 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void create_spc_token(t_token **tokens)
{
	t_token *new_token;

	if(*tokens && ms_strcmp((*tokens)->content," "))
	{
		printf("bou");
		return;
	}

	new_token = malloc_token();
	new_token->content = " ";
	token_add_back(tokens,new_token);
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
