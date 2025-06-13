/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 22:11:44 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/12 19:26:31 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_permited(char *path)
{
	struct stat st;
	if(stat(path, &st) == -1)
		return (0);
	return(st.st_mode & S_IXUSR);
}

int is_file(char *path)
{
	struct stat st;
	if(stat(path, &st) == -1)
		return (0);
	return(S_ISREG(st.st_mode));
}

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

void free_dirs(char **dirs)
{
	int i;
	
	i = 0;
	while(dirs[i])
	{
		free(dirs[i]);
		i ++;
	}
	free(dirs);
}

int ms_execvp(char *file, char **argv,t_shell *s)
{
	char *path;
	char *tmp;
	char **dirs;
	int i;
	//int temp_errno;
	
	i = 0;
	if(ft_strchr(file, '/'))
		if(execve(file,argv,s->env) == -1)
			return (errno);
	if(!argv)
		return (0);
	path = ms_getenv("PATH",s);
	if (!path)
	{
		printf("Minishell : error: $PATH doesn't exist.");
		return (127);
	}
	dirs = ft_split(path,':');
	free(path);
	while(dirs[i])
	{
		tmp = ft_strjoin("/",file);
		path = ft_strjoin(dirs[i],tmp);
		free(tmp);
		if(is_executable(path))
		{
			if (execve(path,argv,s->env) == -1)
			{
				free(path);
				free_dirs(dirs);
				//printf("hello\n");
				return (errno);
			}
			free_dirs(dirs);
			free(path);
			return (1);
		}
		//free_dirs(dirs);
		free(path);
		i ++;
	}
	i = 0;
	free_dirs(dirs);
	return (g_exitcode);
}

