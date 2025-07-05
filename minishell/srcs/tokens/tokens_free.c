/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:56:45 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/04 01:42:06 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_free_tokens(t_token **lst)
{
	t_token *prev;
	t_token *cur;
	
	if(!*lst)
	{
		free(lst);
		return ;
	}
	cur = *lst;
	prev = cur;
	while(cur)
	{
		if(cur->content)
			free(cur->content);
		prev = cur;
		cur = cur->next;
		free(prev);
	}
	free(lst);
}
