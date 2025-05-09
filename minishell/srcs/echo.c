/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:09:39 by vanfossi          #+#    #+#             */
/*   Updated: 2025/05/09 09:09:41 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_echo(t_job *j, t_shell *s)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (ms_strcmp(j->args[i], " "))
		i++;
	while (j->args[i])
	{
		if (ms_strcmp(j->args[i], "-n"))
		{
			n = 1;
			i ++;
			continue ;
		}
		ft_printf("%s", j->args[i]);
		i ++;
	}
	if (!n)
		ft_printf("\n");
}