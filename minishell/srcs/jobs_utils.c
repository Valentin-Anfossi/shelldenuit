/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:28:18 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/22 05:28:48 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_job	*malloc_job(void)
{
	t_job *job;
	
	job = (t_job *)malloc(sizeof(t_job));
	job->args = (char **)malloc(sizeof(char **));
	job->redir = (t_redir *)malloc(sizeof(char **));
	job->cmd = NULL;
	job->error = 0;
	job->piped_job = NULL;
	return (job);
}

int check_for_commands(char *content)
{
	
	if (!ms_strcmp("echo", ft_strtrim(content, "\"\'")))
	return (1);
	else if(!ms_strcmp("cd", ft_strtrim(content, "\"\'")))
	return (1);
	else if(!ms_strcmp("pwd", ft_strtrim(content, "\"\'")))
	return (1);
	else if(!ms_strcmp("export", ft_strtrim(content, "\"\'")))
	return (1);
	else if(!ms_strcmp("unset", ft_strtrim(content, "\"\'")))
	return (1);
	else if(!ms_strcmp("env", ft_strtrim(content, "\"\'")))
	return (1);
	else if(!ms_strcmp("exit", ft_strtrim(content, "\"\'")))
	return (1);
	return (0);
}