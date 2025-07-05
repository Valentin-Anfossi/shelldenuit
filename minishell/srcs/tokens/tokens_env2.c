/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:34:30 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/05 17:35:45 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ms_env_get(char *str, char *out, int i, t_shell *s)
{
	int		pos;
	char	*var;
	char	*env;

	i ++;
	pos = i;
	if (!str[pos])
		env = ft_strdup("");
	else if (str[pos] == '?')
		env = ft_itoa(g_exitcode);
	else if (ft_isdigit(str[pos]))
		env = ft_strdup("");
	else if (!ft_isalpha(str[pos]))
		env = ft_strdup("$");
	else
	{
		while (ft_isalpha(str[pos]))
			pos ++;
		var = ft_substr(str, i, pos - i);
		env = ms_getenv(var, s);
		free(var);
	}
	var = ft_strjoin(out, env);
	free(env);
	return (var);
}
