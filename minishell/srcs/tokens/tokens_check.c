/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:17:28 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/14 16:28:03 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ms_tokens_check(t_token **t)
{
	t_token *cur;

	cur = *t;
	while(cur)
	{
		if((cur->type >= 3 && cur->type <= 6) || cur->type == HERS)
		{
			if(!cur->next)
				return(ms_error_syntax(cur->next));
			if(cur->next == NULL || !ms_token_isarg(cur->next))
				return(ms_error_syntax(cur));
			cur = cur->next->next;
		}
		else if(cur->type == PIP || cur->type == INV)
		{
			if(ms_tokens_pipcheck(cur,t))
				return(ms_error_syntax(cur));
			cur = cur->next;
		}
		else if (ms_token_isarg(cur))
			cur = cur->next;
		else
			return(ms_error_syntax(cur));
	}
	return (1);
}

int ms_tokens_pipcheck(t_token *cur, t_token **t)
{
	if(cur == *t || !cur->next || (!ms_token_isarg(cur->next) &&
	 (cur->next->type < OUT && cur->next->type > HER)))
	 {
		return (1);
	 }
	else
		return(0);
}
int ms_error_syntax(t_token *t)
{
	if(!t)
		ft_putstr_fd("☠️  MinisHell: syntax error near unexpected token 'newline'\n", STDERR_FILENO);
	else if(t->type == PIP || t->type == INV)
	{
		ft_putstr_fd("☠️  MinisHell: syntax error near unexpected token '", STDERR_FILENO);
		ft_putstr_fd(t->content, STDERR_FILENO);
		ft_putstr_fd("'\n",STDERR_FILENO);
	}
	else if(t->next)
	{
		ft_putstr_fd("☠️  MinisHell: syntax error near unexpected token '", STDERR_FILENO);
		ft_putstr_fd(t->next->content, STDERR_FILENO);
		ft_putstr_fd("'\n",STDERR_FILENO);
	}
	else
		ft_putstr_fd("☠️  MinisHell: syntax error near unexpected token 'newline'\n", STDERR_FILENO);
	g_exitcode = 2;
	return (0);
}
