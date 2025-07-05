/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirerror.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 01:56:43 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/05 02:15:08 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ms_redir_error(char *str, int *out_fd, int *in_fd)
{
	if(*out_fd != -1)
		close(*out_fd);
	if(*in_fd != -1)
		close(*in_fd);
	if(ft_strlen(str) == 0)
		return (0);
	if (is_file(str) && !is_permited(str))
	{
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		g_exitcode = 126;
	}
	if (is_file(str) == 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		g_exitcode = 1;
	}
	return (g_exitcode);
}