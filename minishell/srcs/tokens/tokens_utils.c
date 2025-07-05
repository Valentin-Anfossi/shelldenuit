/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:15:50 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/05 17:39:43 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_redir_type(t_token *t)
{
	if (ms_strcmp(t->content, "<"))
		return (R_IN);
	else if (ms_strcmp(t->content, ">"))
		return (R_OUT);
	else if (ms_strcmp(t->content, ">>"))
		return (R_APPEND);
	else if (ms_strcmp(t->content, "<<"))
		return (R_HEREDOC);
	else
		return (0);
}

void	ms_lstdelone(t_token *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
}
