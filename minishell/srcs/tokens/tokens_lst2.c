/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_lst2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 08:59:51 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/05 18:24:25 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokenlst	*ms_create_tlst(char *line, t_token **t)
{
	t_tokenlst	*tlst;

	tlst = (t_tokenlst *)malloc(sizeof(t_tokenlst));
	tlst->line = line;
	tlst->start = 0;
	tlst->end = 0;
	tlst->in_doubles = 0;
	tlst->in_singles = 0;
	tlst->t = t;
	return (tlst);
}

void	ms_lst_doubles(t_tokenlst *tlst)
{
	if (tlst->in_doubles)
	{
		ms_token_create(tlst->line, tlst->start, tlst->end + 1, tlst->t);
		tlst->start = tlst->end + 1;
		tlst->in_doubles = 0;
	}
	else if (ft_strchr(&tlst->line[tlst->end + 1], '"'))
	{
		ms_token_split(tlst->line, tlst->start, tlst->end, tlst->t);
		tlst->start = tlst->end;
		tlst->in_doubles = 1;
	}
}

void	ms_lst_singles(t_tokenlst *tlst)
{
	if (tlst->in_singles)
	{
		ms_token_create(tlst->line, tlst->start, tlst->end + 1, tlst->t);
		tlst->start = tlst->end + 1;
		tlst->in_singles = 0;
	}
	else if (ft_strchr(&tlst->line[tlst->end + 1], '\''))
	{
		ms_token_split(tlst->line, tlst->start, tlst->end, tlst->t);
		tlst->start = tlst->end;
		tlst->in_singles = 1;
	}
}

void	ms_lst_spaces(t_tokenlst *tlst)
{
	if (tlst->start != tlst->end)
		ms_token_split(tlst->line, tlst->start, tlst->end, tlst->t);
	tlst->start = tlst->end + 1;
	if (tlst->line[tlst->end + 1] && !ft_isspace(tlst->line[tlst->end + 1]))
		ms_token_create(" ", 0, 1, tlst->t);
}

void	*ms_free_tlst(t_tokenlst *tlst)
{
	if (!tlst)
		return (NULL);
	free(tlst);
	return (NULL);
}
