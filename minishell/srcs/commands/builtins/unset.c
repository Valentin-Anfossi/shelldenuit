/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:25:00 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/12 19:25:47 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	remove_env(t_shell *s, int index)
{
	if (s->env[index + 1])
	{
		s->env[index] = ft_strdup(s->env[index + 1]);
		index ++;
		while (s->env[index])
		{
			s->env[index] = ft_strdup(s->env[index + 1]);
			index ++;
		}
	}
	else
		s->env[index] = NULL;
}

int	unset_env(t_shell *s, char *str)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(str);
	while (s->env[i])
	{
		if (!ft_strncmp(s->env[i], str, len))
		{
			if (s->env[i][len] && s->env[i][len] == '=')
			{
				remove_env(s, i);
				return (1);
			}
		}
		i ++;
	}
	return (0);
}

int	command_unset(t_job *j, t_shell *s)
{
	int		k;

	k = 1;
	while (j->args[k])
	{
		if (unset_env(s, j->args[k]))
			return (0);
		k ++;
	}
	return (0);
}
