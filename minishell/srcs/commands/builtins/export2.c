/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 02:49:57 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/05 14:19:40 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ms_export_valid(char *str, t_shell *s)
{
	char	*eq_pos;
	size_t	name_len;
	int		i;

	i = 0;
	eq_pos = ft_strchr(str, '=');
	if (eq_pos)
		name_len = (size_t)(eq_pos - str);
	else
		name_len = ft_strlen(str);
	while (s->env[i])
	{
		if (ft_strncmp(s->env[i], str, name_len) == 0
			&& s->env[i][name_len] == '=')
		{
			free(s->env[i]);
			s->env[i] = ft_strdup(str);
			return (1);
		}
		i++;
	}
	return (ms_export_add(s, str));
}

void	ms_free_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
		free(env[i++]);
	free(env);
}
