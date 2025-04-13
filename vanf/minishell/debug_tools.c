/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:20:05 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/13 19:29:44 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void debug_print_tokens(s_token **tokens)
{
	int i;
	
	s_token *cur_token;
	i = 0;
	if(!tokens)
	{
		printf("No token list to print !\n");
		return;
	}
	cur_token = *tokens;
	printf("-=Tokens print=-\n");
	while(cur_token)
	{
		printf("{Type:%d Content:\"%s\"} ",cur_token->type, cur_token->now);
		cur_token = cur_token->next;
		i++;
	}
	printf("\n-=End=-\n");
}