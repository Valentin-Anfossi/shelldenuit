/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:16:56 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/24 04:59:31 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../minishell.h"

int	err_exp_ident(char *str)
{
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
	g_exitcode = 1;
	return (g_exitcode);
}

int	err_cmd_nfound(char *str)
{
	if(ft_strlen(str) == 0)
		return (0);
	if (is_str_exec(str) && is_folder(str) >= 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		if (!is_permited(str))
			ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		else
			ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		g_exitcode = 126;
	}
	else
	{
		if (is_str_exec(str) && is_file(str) == 0)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		}
		else
		{
			ft_putstr_fd(str, STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
		}
		g_exitcode = 127;
	}
	return (g_exitcode);
}
