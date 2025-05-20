/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:23:30 by vanfossi          #+#    #+#             */
/*   Updated: 2025/05/20 17:48:49 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ms_pathup(char *path, int n)
{
	char **s;
	int i;

	i = ft_strlen(path)-1;
	while(path[i])
	{
		if(path[i] == '/')
			return(ft_substr(path,0,i));
		i --;
	}
	return (NULL);
}

void	command_cd(t_job *j, t_shell *s)
{
	DIR *dir;
	char *path;
	char **p;
	int i;

	i = 0;
	if (!j->args[0])
		return;
	if (j->args[1])
	{
		ft_printf("cd: too many arguments\n");
		return ;
	}
	else
	{
		path = j->args[0];
		if(opendir(path))
		{
			p = ft_split(path,'/');
			while(p[i])
			{
				if(ms_strcmp(p[i],".."))
				{
					printf("%s",ms_pathup(s->cwd,1));
					modif_export(s, "PWD", ms_pathup(ms_getenv("PWD",s),1));
					s->cwd = ms_pathup(s->cwd,1);
					printf("o:%s\n",p[i]);
				}
				i ++;
			}
		}
		else
		{
			if(is_folder(path) == 0)
				ft_printf("cd: %s: Not a directory\n",j->args[0]);
			else
				ft_printf("cd: %s: No such file or directory\n",j->args[0]);
			return;
		}
	}
}




void	command_pwd(t_job *j, t_shell *s)
{
	ft_printf("%s\n",ms_getenv("PWD", s));
}