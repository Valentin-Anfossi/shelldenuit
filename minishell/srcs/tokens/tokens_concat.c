/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_concat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:54:36 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/13 12:10:25 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_lst_concat(t_token **t)
{
	t_token *cur;

	cur = *t;
	while(cur)
	{
		if(ms_token_isarg(cur) && cur->next)
		{
			if(ms_token_isarg(cur->next))
			{
				ms_token_concat(cur,cur->next);
			}
			else
				cur = cur->next;
		}
		else
			cur = cur->next;		
	}
}

int		ms_token_isarg(t_token *t)
{
	if(!t)
		return (0);
	if(t->type == ARG)
		return (1);
	else if(t->type == SQ || t->type == DBQ)
		return (1);
	else
		return (0);
}

void	ms_token_concat(t_token *t, t_token *n)
{
	char *tmp;
	
	tmp = ft_strjoin(t->content, n->content);
	free(t->content);
	t->content = tmp;
	t->next = n->next;
	free(n->content);
	free(n);
}