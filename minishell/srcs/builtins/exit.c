/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:51:25 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/03 06:19:18 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	command_exit(t_shell *s, t_job *j)
{
	int	i;

	i = 0;
	free_shell(s);
	if (j->args[2])
	{
		ft_putstr_fd(" too many arguments", STDERR_FILENO);
		exit(1);
	}
	else if (j->args[1])
	{
		while (j->args[1][i])
		{
			if (ft_isalpha(j->args[1][i]))
			{
				ft_putstr_fd(" numeric argument required", STDERR_FILENO);
				exit(2);
			}
			i ++;
		}
		exit(ft_atoi(j->args[1]));
	}
	else
		exit(s->exit_code);
}
