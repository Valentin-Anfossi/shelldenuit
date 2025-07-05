/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execvp2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:13:56 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/05 15:14:16 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_permited(char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (0);
	return (st.st_mode & S_IXUSR);
}

int	is_file(char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (0);
	return (S_ISREG(st.st_mode));
}

int	is_executable(char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (0);
	return (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR));
}

int	is_folder(char *path)
{
	struct stat	st;

	if (stat(path, &st) == -1)
		return (-1);
	return (S_ISDIR(st.st_mode));
}

void	free_dirs(char **dirs)
{
	int	i;

	i = 0;
	while (dirs[i])
	{
		free(dirs[i]);
		i ++;
	}
	free(dirs);
}
