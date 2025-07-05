/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:51:25 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/05 14:20:04 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	command_exit(t_shell *s, t_job *j)
{
	if (ms_charraylen(j->args) > 2)
	{
		ft_putstr_fd("exit : too many arguments\n", STDERR_FILENO);
		exit(1);
	}
	else if (j->args[1])
	{
		command_exit_helper(j->args[1]);
		free_shell(s);
		free_jobs(j);
		exit(g_exitcode);
	}
	else
	{
		free_shell(s);
		free_jobs(j);
		exit(g_exitcode);
	}
}

void	command_exit_helper(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
		{
			ft_putstr_fd("exit : numeric argument required\n", STDERR_FILENO);
			g_exitcode = 2;
			return ;
		}
		i ++;
	}
	g_exitcode = ft_atoi(str);
}
