/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:47:44 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/29 14:47:44 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	select_command(t_job *jobs, t_shell *s)
{
	t_job *j;

	j = jobs;
	if (j->cmd)
	{
		if (ms_strcmp(j->cmd, "echo"))
			return (command_echo(j));
		else if (ms_strcmp(j->cmd, "env"))
			return (command_env(s));
		else if (ms_strcmp(j->cmd, "export"))
			return (ms_command_export(j, s));
		else if (ms_strcmp(j->cmd, "cd"))
			return (command_cd(j, s));
		else if (ms_strcmp(j->cmd, "unset"))
			return (ms_command_unset(j, s));
		else if (ms_strcmp(j->cmd, "pwd"))
			return (command_pwd());
		else if (ms_strcmp(j->cmd, "exit"))
			return (command_exit(s, j), 0);
	}
	return (1);
}
