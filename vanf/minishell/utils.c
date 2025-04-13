/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:41:51 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/13 20:26:22 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

s_token	*token_last(s_token *lst)
{
	s_token	*list;

	if (!lst)
		return (0);
	list = lst;
	while (list->next)
		list = list->next;
	return (list);
}

void	token_add_back(s_token **lst, s_token *token)
{
	s_token	*last;

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

int	ms_strcmp(char *str1, char *str2)
{
	int i;

	i = 0;
	while(str1[i])
	{
		if(str2[i] != str1[i] && str2[i] != (str1[i] - 32))
			return (0);
		else
			i++;
	}
	return (1);
}
