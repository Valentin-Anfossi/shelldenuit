/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:09:39 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/05 14:21:59 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	command_echo_option(t_job *j, int *i, int *n)
{
	int	k;

	while (j->args[*i] && j->args[*i][0] && j->args[*i][0] == '-')
	{
		k = 1;
		while (j->args[*i][k] && j->args[*i][k] == 'n')
			k++;
		if (j->args[*i][k] == '\0')
			*n = 1;
		else
			return ;
		(*i)++;
	}
}

int	command_echo(t_job *j)
{
	int	i;
	int	n;

	i = 1;
	n = 0;
	if (ms_charraylen(j->args) > 1)
	{
		command_echo_option(j, &i, &n);
		while (j->args[i])
		{
			ft_putstr_fd(j->args[i], STDOUT_FILENO);
			if (j->args[i + 1])
				ft_putchar_fd(' ', STDOUT_FILENO);
			i++;
		}
	}
	if (!n)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
