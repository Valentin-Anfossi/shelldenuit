/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:08:45 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/13 11:02:35 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


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




