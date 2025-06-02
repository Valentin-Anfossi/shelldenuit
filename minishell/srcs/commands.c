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

#include "minishell.h"

int	select_command(t_job *jobs, t_shell *s)
{
	if (jobs->cmd)
	{
		if (ms_strcmp(jobs->cmd, "echo"))
			command_echo(jobs);
		else if (ms_strcmp(jobs->cmd, "env"))
			command_env(s);
		else if (ms_strcmp(jobs->cmd, "export"))
			command_export(jobs, s);
		else if (ms_strcmp(jobs->cmd, "cd"))
			command_cd(jobs, s);
		else if (ms_strcmp(jobs->cmd, "unset"))
			command_unset(jobs, s);
		else if (ms_strcmp(jobs->cmd, "pwd"))
			command_pwd(s);
		else if (ms_strcmp(jobs->cmd, "exit"))
			command_exit(s);
		else if (ms_strcmp(jobs->cmd, "$?"))
			command_status(jobs,s);
	}
	return (0);
}