/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:23:30 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/05 19:07:39 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_cd_valid(t_job *j)
{
	if (ms_charraylen(j->args) > 2)
	{
		ft_putstr_fd("minishell : cd: too many arguments\n", STDERR_FILENO);
		g_exitcode = 1;
		return (0);
	}
	else
		return (1);
}

void	cd_error(char *path)
{
	if (errno == EACCES)
	{
		ft_putstr_fd("minishell: cd: Permission denied: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		g_exitcode = 1;
	}
	if (errno == ENOENT)
	{
		ft_putstr_fd("minishell: cd:", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		g_exitcode = 1;
	}
	if (errno == ENOTDIR)
	{
		ft_putstr_fd("minishell: cd:", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
		g_exitcode = 1;
	}
}

int	cd_previous(t_shell *s)
{
	char	*tmp;
	char	*tmp_old;

	tmp = ms_getenv("PWD", s);
	tmp_old = ms_getenv("OLDPWD", s);
	ms_setenv("PWD", tmp_old, s);
	ms_setenv("OLDPWD", tmp, s);
	free(s->cwd);
	s->cwd = tmp_old;
	chdir(tmp_old);
	free(tmp);
	return (0);
}

int	cd_home(t_job *j, t_shell *s)
{
	if (!j->args[1])
	{
		ms_setenv("OLDPWD", s->cwd, s);
		free(s->cwd);
		s->cwd = ms_getenv("HOME", s);
		chdir(s->cwd);
		free(s->cwd);
		s->cwd = getcwd(NULL, PATH_MAX);
		ms_setenv("PWD", s->cwd, s);
		return (0);
	}
	else
		return (1);
}

int	command_cd(t_job *j, t_shell *s)
{
	if (!is_cd_valid(j))
		return (1);
	if (!j->args[1])
		return (cd_home(j, s));
	if (ms_strcmp(j->args[1], "-"))
		return (cd_previous(s));
	if (chdir(j->args[1]) == -1)
	{
		cd_error(j->args[1]);
		return (1);
	}
	ms_setenv("OLDPWD", s->cwd, s);
	free(s->cwd);
	s->cwd = getcwd(NULL, PATH_MAX);
	ms_setenv("PWD", s->cwd, s);
	return (0);
}
