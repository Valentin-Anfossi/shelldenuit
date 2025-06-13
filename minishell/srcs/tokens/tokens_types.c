/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:15:10 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/13 18:31:52 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ms_lst_types(t_token **t)
{
	t_token *cur;

	if(!*t)
		return ;
	cur = *t;
	while(cur)
	{
		cur->type = ms_token_type(cur);
		if(cur->type >= 1 && cur->type <= 2)
			ms_token_trim(cur);
		cur = cur->next;
	}
	return ;
}

void ms_token_trim(t_token *t)
{
	char *tmp;

	tmp = ft_strtrim(t->content,"\"\'");
	free(t->content);
	t->content = tmp;
}

int	ms_token_type(t_token *t)
{
	char *s;

	s = t->content;
	if(ms_strcmp(s," "))
		return (SPC);
	else if(ms_strcmp(s,">"))
		return (OUT);
	else if(ms_strcmp(s,">>"))
		return (APP);
	else if(ms_strcmp(s,"<"))
		return (IN);
	else if(ms_strcmp(s,"<<"))
		return (HER);
	else if(ms_strcmp(s,"|"))
		return (PIP);
	else if(ms_strcmp(s,"||") || ms_strcmp(s,"&&") || ms_strcmp(s,"<>"))
		return (INV);
	else if(ms_strcmp(s,"<<<"))
		return (HERS);
	else if(ms_quotes(s) == 1)
		return (SQ);
	else if(ms_quotes(s) == 2)
		return (DBQ);
	else
		return (ARG);	
}

int	ms_quotes(char *s)
{
	int len;

	if(!s)
		return (0);
	len = ft_strlen(s);
	if(s[0] == '\'' && s[len-1] == '\'')
		return (1);
	else if(s[0] == '"' && s[len-1] == '"')
		return (2);
	else
		return (0);
}
