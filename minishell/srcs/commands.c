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

void	command_cd(t_job *j, t_shell *s)
{
	if (j->args[1])
	{
		perror("cd: too many arguments");
		return ;
	}
	if (opendir(j->args[0]))
	{
	}
}

void	select_command(t_job *jobs, t_shell *s)
{
	if (jobs->cmd)
	{
		if (ms_strcmp(jobs->cmd, "echo"))
			command_echo(jobs, s);
		if (ms_strcmp(jobs->cmd, "env"))
			command_env(s);
		if (ms_strcmp(jobs->cmd, "export"))
			command_export(jobs, s);
		if (ms_strcmp(jobs->cmd, "cd"))
			command_cd(jobs, s);
		if (ms_strcmp(jobs->cmd, "unset"))
			command_unset(jobs, s);
	}
}
// void select_command(t_job *job)
// {
// 	char *cmd;

// 	cmd = ft_strtrim(job->cmd,"\'\"");
// 	if(ms_strcmp("cd",cmd))
// 		cmd_cd(job);
// 	else if(ms_strcmp("echo",cmd))
// 		cmd_echo(job);
// 	else if(ms_strcmp("pwd",cmd))
// 		cmd_pwd(job);
// 	else if(ms_strcmp("export",cmd))
// 		cmd_export(job);
// 	else if(ms_strcmp("unset",cmd))
// 		cmd_unset(job);
// 	else if(ms_strcmp("env",cmd))
// 		cmd_env(job);
// 	else if(ms_strcmp("exit",cmd))
// 		cmd_exit(job);
// 	else
// 		is_str_exec(job);
// }

// void is_str_exec(job)
// {
// 	// check si y a un file de merde
// 	ft_printf("error");
// }


// void cmd_exec(t_job *job)
// {

// }
