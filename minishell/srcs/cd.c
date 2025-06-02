/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:23:30 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/02 03:14:41 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int is_cd_valid(t_job *j, t_shell *s)
{
	struct stat st;
	
	if (!j->args[1]) //NO ARGS == CD $HOME
	{
		ms_setenv("OLDPWD",s->cwd,s);
		ms_setenv("PWD",ms_getenv("HOME",s),s);
		s->cwd = ms_getenv("HOME",s);
		chdir(s->cwd);
		return (0);
	}
	else if (j->args[2])
	{
		write(STDERR_FILENO,"minishell : cd: too many arguments\n",36);
		s->exit_code = 1;
		return (0);
	}
	else
		return (1);
}

void	cd_error(t_shell *s, char *path)
{
	if(errno == EACCES)
	{
		write(STDERR_FILENO,"cd: Permission denied: ",23);
		write(STDERR_FILENO,path,ft_strlen(path));
		write(STDERR_FILENO,"\n",1);			
	}
	if(errno == ENOENT)
	{
		write(STDERR_FILENO,"cd: No such directory: ",24);
		write(STDERR_FILENO,path,ft_strlen(path));
		write(STDERR_FILENO,"\n",1);			
	}
	if(errno == ENOTDIR)
	{
		write(STDERR_FILENO,"cd: Not a directory: ",22);
		write(STDERR_FILENO,path,ft_strlen(path));
		write(STDERR_FILENO,"\n",1);			
	}
}

void cd_previous(t_shell *s)
{
	char *tmp;
	char *tmp_old;

	tmp = ms_getenv("PWD",s);
	tmp_old = ms_getenv("OLDPWD",s);

	ms_setenv("PWD", tmp_old, s);
	ms_setenv("OLDPWD", tmp, s);
	free(s->cwd);
	s->cwd = tmp_old;
	chdir(tmp_old);
	free(tmp);
	free(tmp_old);
}

// A FINIR
void	command_cd(t_job *j, t_shell *s)
{
	char *path;
	char **p;
	int i;

	i = 0;
	if(!is_cd_valid(j,s))
		return ;
	if(ms_strcmp(j->args[1],"-"))
		return (cd_previous(s));
	if(chdir(j->args[1]) == -1)
	{
		cd_error(s,j->args[1]);
		return ;
	}
	ms_setenv("OLDPWD",s->cwd,s);
	s->cwd = getcwd(s->cwd,PATH_MAX);
	ms_setenv("PWD",s->cwd,s);
	printf("%s",s->cwd);
}




void	command_pwd(t_shell *s)
{
	char *buff;
	buff = getcwd(NULL,PATH_MAX);
	ft_printf("%s\n",buff);
	free(buff);
}