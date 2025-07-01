/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:09:39 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/12 21:43:33 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	command_echo_skip(t_job *j, int *i, int *n)
{
	while ((j->args[*i] && ms_strcmp(j->args[*i], " ")) || ms_strcmp(j->args[*i], "-n"))
	{
		if (ms_strcmp(j->args[*i], "-n"))
			*n = 1;
		(*i)++;
	}
}

int	command_echo(t_job *j)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (ms_charraylen(j->args) < 2)
		return (0);
	//command_echo_skip(j, &i, &n);
	while (j->args[i])
	{
		if (ms_strcmp(j->args[i], "-n"))
		{
			n = 1;
			i ++;
			continue ;
		}
		printf("%s", j->args[i]);
		if (j->args[i + 1])
			printf(" ");
		i ++;
	}
	if (!n)
		printf("\n");
	return (0);
}
