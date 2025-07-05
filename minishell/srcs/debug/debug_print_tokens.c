/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 08:58:11 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/05 14:29:49 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_debug_print_tokens(t_token **tokens)
{
	t_token	*cur_token;

	if (!tokens || !(*tokens))
	{
		printf("No token list to print !\n");
		return ;
	}
	cur_token = *tokens;
	while (cur_token)
	{
		if (!cur_token->content)
			printf("{%d:NULL}", cur_token->type);
		else
			printf("{%d:%s}", cur_token->type, cur_token->content);
		cur_token = cur_token->next;
	}
	printf("\n");
}
