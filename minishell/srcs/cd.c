/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:23:30 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/01 03:52:49 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ms_pathup(char *path)
{
	int i;

	i = (ft_strlen(path)) - 1;
	while(path[i])
	{
		if(path[i] == '/')
			return(ft_substr(path,0,i+1));
		i --;
	}
	return (path);
}

int is_cd_valid(t_job *j, t_shell *s)
{
	struct stat st;
	
	if (!j->args[1]) //NO ARGS == CD $HOME
	{
		modif_export(s,"OLDPWD",ft_strjoin("OLDPWD=",s->cwd));
		s->cwd = ms_getenv("HOME",s);
		modif_export(s,"PWD",ft_strjoin("PWD=",s->cwd));
	}
	else if (j->args[2])
	{
		write(STDERR_FILENO,"minishell : cd: too many arguments\n",36);
		s->exit_code = 1;
		return (0);
	}
}

char *cd_create_path(char *str, t_shell *s)
{
	char *path;
	
	if(str && str[0] != '/') // RELATIVE
	{
		path = ft_strjoin(s->cwd,"/");
		path = ft_strjoin(path,str);
	}
	else // ABSOLUTE
	{
		path = str;
	}
	return (path);
}

// NEEDS TO BE REDONE (je sais pas ce que j'ai fais mais c'est completement debile lol)
void	command_cd(t_job *j, t_shell *s)
{
	char *path;
	char **p;
	int i;

	i = 0;
	if(!is_cd_valid(j,s))
		return ;
	path = cd_create_path(j->args[1], s);
	printf("CD PATH :%s\n",path);
}




void	command_pwd(t_shell *s)
{
	ft_printf("%s\n",ms_getenv("PWD", s));
}