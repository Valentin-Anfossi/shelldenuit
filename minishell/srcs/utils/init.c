/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:16:59 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/12 19:17:45 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_shell	*create_shell(void)
{
	extern char	**environ;
	t_shell		*s;
	int			i;

	i = 0;
	s = (t_shell *)malloc(sizeof(t_shell));
	s->cwd = NULL;
	while (environ[i])
		i++;
	s->env = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (environ[i])
	{
		s->env[i] = ft_strdup(environ[i]);
		i++;
	}
	s->env[i] = NULL;
	s->cwd = getcwd(s->cwd, PATH_MAX);
	g_exitcode = 0;
	return (s);
}