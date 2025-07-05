/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execvp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 22:11:44 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/05 18:21:46 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ms_execvp_path(t_execvp *vp)
{
	while (vp->dirs[vp->i])
	{
		vp->tmp = ft_strjoin("/", vp->file);
		vp->path = ft_strjoin(vp->dirs[vp->i], vp->tmp);
		free(vp->tmp);
		if (is_executable(vp->path))
		{
			if (execve(vp->path, vp->argv, vp->s->env) == -1)
			{
				free(vp->path);
				free_dirs(vp->dirs);
				return (1);
			}
			free_dirs(vp->dirs);
			free(vp->path);
			return (1);
		}
		free(vp->path);
		vp->i ++;
	}
	vp->i = 0;
	free_dirs(vp->dirs);
	return (1);
}

int	ms_execquit(int err, t_execvp *vp)
{
	free(vp);
	return (err);
}

int	ms_execvp(char *file, char **argv, t_shell *s)
{
	t_execvp	*vp;
	int			re;

	vp = (t_execvp *)malloc(sizeof(t_execvp));
	vp->i = 0;
	vp->file = file;
	vp->s = s;
	vp->argv = argv;
	if (ft_strchr(file, '/'))
		if (execve(file, argv, s->env) == -1)
			return (ms_execquit(errno, vp));
	if (!argv)
		return (ms_execquit(0, vp));
	vp->path = ms_getenv("PATH", s);
	if (!vp->path)
	{
		printf("Minishell : error: $PATH doesn't exist.");
		return (ms_execquit(127, vp));
	}
	vp->dirs = ft_split(vp->path, ':');
	free(vp->path);
	re = ms_execvp_path(vp);
	free(vp);
	return (re);
}
