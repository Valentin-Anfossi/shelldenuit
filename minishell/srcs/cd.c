/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:23:30 by vanfossi          #+#    #+#             */
/*   Updated: 2025/05/10 03:25:46 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_cd(t_job *j, t_shell *s)
{
	DIR *dir;
	char *path;
	
	if (!j->args[1])
		return;
	if (j->args[2])
	{
		ft_printf("cd: too many arguments\n");
		return ;
	}
	else
	{
		path = j->args[1];
		if(opendir(path))
		{
			if(path[0] == '/') //absolute path
				s->cwd = ft_strdup(path);
			else // relative path
			{
				path = ft_strjoin("/",path);
				s->cwd = ft_strjoin(s->cwd,path);
			}
		}
		else
		{
			ft_printf("cd: %s: No such file or directory\n",j->args[1]);
			return;
		}
	}
}

void	command_pwd(t_job *j, t_shell *s)
{
	ft_printf("%s\n",s->cwd);
}