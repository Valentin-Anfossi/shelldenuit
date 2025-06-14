/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:51:25 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/12 19:25:37 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	command_exit(t_shell *s, t_job *j)
{
	int	i;

	i = 0;
	if (ms_charraylen(j->args) > 2)
	{
		ft_putstr_fd("exit : too many arguments\n", STDERR_FILENO);
		exit(1);
	}
	else if (j->args[1])
	{
		while (j->args[1][i])
		{
			if (ft_isalpha(j->args[1][i]))
			{
				ft_putstr_fd("exit : numeric argument required\n", STDERR_FILENO);
				exit(2);
			}
			i ++;
		}
		g_exitcode = ft_atoi(j->args[1]);
		if(g_exitcode < 0)
			
		//printf("EXIT : %d\n",g_exitcode);
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
