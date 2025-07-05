/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:49:22 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/05 18:21:17 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//Split in two at first encounter of char c
//Returns NULL if character not found
char	**ms_split(char *string, int c)
{
	int		i;
	char	**out;

	i = 0;
	while (string[i] && string[i] != c)
		i ++;
	if (i + 1 >= (int)ft_strlen(string))
		return (NULL);
	out = (char **)malloc(sizeof(char *) * 3);
	out[0] = (char *)malloc(i + 2);
	ft_strlcpy(out[0], string, i + 1);
	string ++;
	string += i;
	out[1] = ft_strdup(string);
	out[2] = NULL;
	return (out);
}

char	*ms_getenv(char *key, t_shell *s)
{
	int		i;
	char	**actual;
	char	*out;
	int		match;

	out = NULL;
	i = 0;
	while (s->env[i])
	{
		actual = ms_split(s->env[i], '=');
		match = 0;
		if (actual)
		{
			match = ms_strcmp(actual[0], key);
			if (match)
				out = ft_strdup(actual[1]);
			free(actual[0]);
			free(actual[1]);
			free(actual);
			if (match)
				break ;
		}
		i++;
	}
	return (out);
}

void	free_shell(t_shell *s)
{
	int	i;

	i = 0;
	while (s->env[i])
	{
		free(s->env[i]);
		i ++;
	}
	free(s->env);
	if (s->cwd)
		free(s->cwd);
	free(s);
}

int	startswith(char *s, char *start)
{
	int	i;

	i = 0;
	if (!s || !start)
		return (0);
	while (start[i])
	{
		if (s[i] != start[i] && s[i])
		{
			return (0);
		}
		i ++;
	}
	return (1);
}

int	is_str_cmd(char *t)
{
	int		i;
	char	*s;

	i = 0;
	s = ft_strtrim(t, "\'\"");
	while (ms_cmdlst()[i])
	{
		if (ms_strcmp(ms_cmdlst()[i], s))
		{
			free(s);
			return (1);
		}
		else if (is_str_exec(t))
		{
			free(s);
			return (0);
		}
		i ++;
	}
	free(s);
	return (0);
}
