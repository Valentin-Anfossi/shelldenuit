/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:41:51 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/17 03:19:03 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Return last token from lst
t_token	*token_last(t_token *lst)
{
	t_token	*list;

	if (!lst)
		return (0);
	list = lst;
	while (list->next)
		list = list->next;
	return (list);
}

//Add token to the back of lst
void	token_add_back(t_token **lst, t_token *token)
{
	t_token	*last;

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

//Compare 2 strings, return 1 if theyre the same
int	ms_strcmp(char *str1, char *str2)
{
	int i;

	i = 0;
	// if(ft_strlen(str1) != ft_strlen(str2))
	// 	return (0);

	while(str1[i] && str2[i])
	{
		if(str2[i] != str1[i])
			return (0);
		if(str2[i] != (str1[i] - 32))
			return (0);
		else
			i++;
	}
	return (1);
}
int	ms_lstsize(t_token *lst)
{
	t_token	*list;
	int		i;

	list = lst;
	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

t_token *malloc_token(void)
{
	t_token *new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	new_token->type = 0;
	new_token->content = NULL;
	new_token->next = NULL;
	return (new_token);
}
void debug_print_tokens(t_token **tokens)
{
	int i;
	
	t_token *cur_token;
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
		if(!cur_token->content)
			printf("{Type:%d} ",cur_token->type);
		else
			printf("{%s} ",cur_token->content);
		cur_token = cur_token->next;
		i++;
	}
	printf("\n-=End=-\n");
}