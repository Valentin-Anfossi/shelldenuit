/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 08:50:07 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/13 19:42:54 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token **ms_tokens(char *line, t_shell *s)
{
	t_token **t;

	if (ft_strlen(line) == 0)
		return (NULL);
	t = ms_lst_tokens(line);
	ms_lst_types(t);
	ms_token_env(t, s);
	ms_lst_concat(t);
	ms_rmv_spaces(t);
	//ms_debug_print_tokens(t);
	if(!ms_tokens_check(t))
	{
		free_tokens(t);
		return (NULL);
	}
	add_history(line);
	return (t);
}

void ms_rmv_spaces(t_token **t)
{
    t_token *cur = *t;
    t_token *prev = NULL;
    t_token *to_free;

    while (cur)
    {
        if (cur->type == SPC)
        {
            to_free = cur;
            
            // Update links
            if (prev == NULL)
                *t = cur->next;    // Update head pointer
            else
                prev->next = cur->next;
            
            // Move to next node
            cur = cur->next;
            
            // Free the SPC node
            free(to_free->content);
            free(to_free);
        }
        else
        {
            prev = cur;
            cur = cur->next;
        }
    }
}

t_token	**ms_lst_tokens(char *line)
{
	t_tokenlst *tlst;
	t_token	**tokens;

	tokens = (t_token **)malloc(sizeof(t_token *));
	*tokens = NULL;
	tlst = ms_create_tlst(line,tokens);
	while (line[tlst->start] && ft_isspace(line[tlst->start]))
		tlst->start ++;
	tlst->end = tlst->start;
	while (line[tlst->end])
	{
		if (line[tlst->end] == '"' && !tlst->in_singles)
			ms_lst_doubles(tlst);
		else if (line[tlst->end] == '\'' && !tlst->in_doubles)
			ms_lst_singles(tlst);
		else if (ft_isspace(tlst->line[tlst->end]) && !tlst->in_doubles && !tlst->in_singles)
			ms_lst_spaces(tlst);
		tlst->end++;
	}
	if (tlst->start < tlst->end)
		ms_token_split(tlst->line, tlst->start, tlst->end, tlst->t);
	ms_free_tlst(tlst);
	return (tokens);
}
