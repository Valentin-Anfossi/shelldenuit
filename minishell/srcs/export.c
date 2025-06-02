/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:20:30 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/02 08:41:12 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_export(char **vars, t_shell *shell, char *str)
{
	int		i;
	char	*env;

	i = 0;
	if (!vars)
		return (0);
	if (vars && vars[0] && vars[1])
	{
		if (vars[0][0] >= '0' && vars[0][0] <='9')
			return (err_exp_ident(str));
		i = 1;
		env = ms_getenv(vars[0], shell);
		if (env)
			return (2);
		else if (!ft_isalpha(vars[0][0]))
			return (0);
		while (vars[0][i])
		{
			if (!ft_isalnum(vars[0][i]) && vars[0][i] != '_')
				return (0);
			i ++;
		}
	}
	return (1);
}


void	add_to_env(t_shell *s, char *add_env)
{
	int		i;
	int		j;
	char	**new_env;

	j = 0;
	i = 0;
	while (s->env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (s->env[i])
	{
		new_env[i] = ft_strdup(s->env[i]);
		i++;
	}
	new_env[i] = ft_strdup(add_env);
	new_env[i + 1] = NULL;
	while (s->env[j])
	{
		free(s->env[j]);
		j++;
	}
	free(s->env);
	s->env = new_env;
}

void	modif_export(t_shell *s, char *vars, char *newstr)
{
	int	i;

	i = 0;
	while (ft_strncmp(s->env[i], vars, ft_strlen(vars)) != 0)
		i++;
	free(s->env[i]);
	s->env[i] = ft_strdup(newstr);
}

int	command_export(t_job *j, t_shell *s)
{
	char	**vars;
	int		k;

	k = 1;
	while (j->args[k])
	{
		vars = ms_split(j->args[k], '=');
		if (check_export(vars, s, j->args[k]))
		{
			if (check_export(vars, s, j->args[k]) == 2)
			{
				modif_export(s, vars[0], j->args[k]);
				return (0);
			}
			else
			{
				add_to_env(s, j->args[k]);
				return (0);
			}
		}
		k ++;
	}
	return (1);
}
