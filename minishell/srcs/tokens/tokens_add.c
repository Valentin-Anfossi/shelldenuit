/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:01:17 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/13 11:14:42 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ms_token_malloc(void)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->type = 0;
	new_token->content = NULL;
	new_token->next = NULL;
	return (new_token);
}

void	ms_token_create(char *line, int start, int end, t_token **tokens)
{
    t_token *new_token;

    if (end <= start || !line)
        return;
    new_token = ms_token_malloc();
    if (!new_token)
        return;
    new_token->content = ft_substr(line, start, (end - start));
    if (!new_token->content)
    {
        free(new_token);
        return;
    }
    new_token->next = NULL;
    if (!*tokens)
        *tokens = new_token;
    else
    {
        t_token *last = *tokens;
        while (last->next)
            last = last->next;
        last->next = new_token;
    }
}
