/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:40:47 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/05 17:41:01 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	combiendetoks(t_token **t)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = *t;
	while (temp)
	{
		temp = temp->next;
		i ++;
	}
	return (i);
}
