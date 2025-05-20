/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 22:11:44 by vanfossi          #+#    #+#             */
/*   Updated: 2025/05/20 14:31:11 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_executable(char *path)
{
	struct stat st;
	if(stat(path, &st) == -1)
		return (0);
	return(S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR));
}

int is_folder(char *path)
{
	struct stat st;
	if(stat(path, &st) == -1)
		return (-1);
	return(S_ISDIR(st.st_mode));
}

int ms_execvp(char *file, char **argv,t_shell *s)
{
	char *path;
	char **dirs;
	int i;
	
	i = 0;
	if(ft_strchr(file, '/'))
	{
		if(execve(file,argv,s->env) == -1)
			return (errno);
	}
	path = ms_getenv("PATH",s);
	if (!path)
	{
		printf("PATH doesn't exist.");
		return (1);
	}
	dirs = ft_split(path,':');
	while(dirs[i])
	{
		path = ft_strjoin(dirs[i],ft_strjoin("/",file));
		if(is_executable(path))
		{
			if (execve(path,argv,s->env) == -1)
				return (errno);
		}
		i ++;
	}
}
