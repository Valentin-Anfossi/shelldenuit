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
	if (jobs->cmd)
	{
		if (ms_strcmp(jobs->cmd, "echo"))
			return (command_echo(jobs));
		else if (ms_strcmp(jobs->cmd, "env"))
			return (command_env(s));
		else if (ms_strcmp(jobs->cmd, "export"))
			return (ms_command_export(jobs, s));
		else if (ms_strcmp(jobs->cmd, "cd"))
			return (command_cd(jobs, s));
		else if (ms_strcmp(jobs->cmd, "unset"))
			return (ms_command_unset(jobs, s));
		else if (ms_strcmp(jobs->cmd, "pwd"))
			return (command_pwd());
		else if (ms_strcmp(jobs->cmd, "exit"))
			return (command_exit(s, jobs), 0);
	}
	return (1);
}
