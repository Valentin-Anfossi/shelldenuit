/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:41:51 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/22 05:24:04 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Compare 2 strings, return 0 if theyre the same
int	ms_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
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

void	debug_print_tokens(t_token **tokens)
{
	t_token	*cur_token;

	if (!tokens)
	{
		printf("No token list to print !\n");
		return ;
	}
	cur_token = *tokens;
	while (cur_token)
	{
		if (!cur_token->content)
			printf("{Type:%d} ", cur_token->type);
		else
			printf("{%d:%s}", cur_token->type, cur_token->content);
		cur_token = cur_token->next;
	}
	printf("\n");
}

void	debug_print_job(t_job **jobs)
{
	t_job	*job;
	int		i;

	job = *jobs;
	if (!jobs)
	{
		ft_printf("No job");
		return ;
	}
	while (job)
	{
		i = 0;
		if (job->error != 0)
			ft_printf("ERROR\n");
		if (job->cmd)
			ft_printf("CMD : %s\n", job->cmd);
		while (job->args[i])
		{
			ft_printf("ARG %d : %s ; ", i, job->args[i]);
			i++;
		}
		if (job->piped_job == NULL)
			break ;
		else
		{
			job = job->piped_job;
			ft_printf("\n");
		}
	}
	ft_printf("\n");
}
