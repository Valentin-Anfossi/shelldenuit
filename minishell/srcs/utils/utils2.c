/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:48:27 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/05 18:21:25 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ms_fix_args(t_job *job)
{
	char	**args;
	int		i;
	int		j;

	i = 0;
	j = 0;
	args = (char **)malloc(sizeof(char *) * (ms_charraylen(job->args) + 2));
	i = 0;
	args[j] = ft_strdup(job->cmd);
	j++;
	while (job->args[i])
	{
		if (!ms_strcmp(" ", job->args[i]))
		{
			args[j] = ft_strdup(job->args[i]);
			j ++;
		}
		free(job->args[i]);
		i ++;
	}
	args[j] = NULL;
	return (args);
}

//Changes env with the value in str. returns 1 if succesful, 0 if error
int	ms_setenv(char *env, char *str, t_shell *s)
{
	char	**split;
	char	*tmp;
	int		i;

	i = 0;
	while (s->env[i])
	{
		split = ft_split(s->env[i], '=');
		if (ms_strcmp(split[0], env))
		{
			free(s->env[i]);
			tmp = ft_strjoin(split[0], "=");
			s->env[i] = ft_strjoin(tmp, str);
			free(tmp);
			ms_free_split(split);
			return (1);
		}
		ms_free_split(split);
		i ++;
	}
	return (0);
}

void	ms_free_split(char **split)
{
	int	i;

	if (!split || !*split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i ++;
	}
	free(split);
}

int	ms_charraylen(char **ar)
{
	int	i;

	i = 0;
	if (!ar)
		return (0);
	while (ar[i])
		i++;
	return (i);
}

int	ms_count_jobs(t_job *job)
{
	int	n;

	n = 0;
	if (!job)
		return (n);
	while (job)
	{
		n ++;
		job = job->piped_job;
	}
	return (n);
}
