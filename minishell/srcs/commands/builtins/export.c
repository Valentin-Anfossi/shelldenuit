/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:20:30 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/12 19:25:42 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_export(char **vars, t_shell *shell, char *str)
{
	int		i;
	char	*env;

	i = -1;
	if (str[0] == '=')
		return (err_exp_ident(str, shell));
	while (str[++i] != '=' && str[i] != '\0')
		if ((!ft_isalpha(str[i]) && str[i] != '_'))
			return (err_exp_ident(str, shell));
	if (!vars)
		return (0);
	if (vars && vars[0] && vars[1])
	{
		if (vars[0][0] >= '0' && vars[0][0] <= '9')
			return (1);
		i = 1;
		env = ms_getenv(vars[0], shell);
		if (env)
			return (2);
		else if (!ft_isalpha(vars[0][0]))
			return (err_exp_ident(str, shell));
		while (vars[0][i])
		{
			if (!ft_isalnum(vars[0][i]) && vars[0][i] != '_')
				return (err_exp_ident(str, shell));
			i ++;
		}
	}
	return (0);
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
	int		check;

	k = 1;
	while (j->args[k])
	{
		vars = ms_split(j->args[k], '=');
		check = check_export(vars, s, j->args[k]);
		if (check == 2)
		{
			modif_export(s, vars[0], j->args[k]);
			return (0);
		}
		else if (check == 0)
		{
			if (vars)
				add_to_env(s, j->args[k]);
			return (0);
		}
		k ++;
	}
	return (1);
}
