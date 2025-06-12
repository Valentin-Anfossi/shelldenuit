/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:08:37 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/12 19:25:33 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	command_env(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell->env)
		return (1);
	while (shell->env[i])
	{
		ft_printf("%s\n", shell->env[i]);
		i ++;
	}
	return (0);
}
