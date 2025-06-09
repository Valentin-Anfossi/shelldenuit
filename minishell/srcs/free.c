/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 05:47:06 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/09 17:55:32 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_tokens(t_token **t)
{
	t_token *temp;
	t_token *prev;
	
	temp = *t;

	while(temp)
	{
		//free(temp->content);
		prev = temp;
		temp = temp->next;
		free(prev);
	}
	if(temp)
	{
		free(temp);
	}
}

void free_all(t_job *j, t_shell *s, t_token **t)
{
	if(j)
		free_jobs(j);		
	if(s)
		free_shell(s);
	if(t)
		free_tokens(t);
}