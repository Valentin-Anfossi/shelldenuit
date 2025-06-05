/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:16:56 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/05 06:13:45 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	err_exp_ident(char *str, t_shell *shell)
{
	ft_putstr_fd("minishell: export: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
	shell->exit_code = 1;
	return (shell->exit_code);
}

int	err_cmd_nfound(char *str, t_shell *shell)
{
	if(ft_strlen(str) == 0)
	{
		shell->exit_code = 0;
		return (shell->exit_code);
	}
	if (is_str_exec(str) && is_folder(str))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
		shell->exit_code = 126;
	}
	else
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		shell->exit_code = 127;
	}
	return (shell->exit_code);
}
