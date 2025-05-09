/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:25:00 by vanfossi          #+#    #+#             */
/*   Updated: 2025/05/09 09:06:33 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void remove_env(t_shell *s, int index)
{
	char *prev;
	char *next;
	
	if (s->env[index+1])
	{
		s->env[index] = ft_strdup(s->env[index+1]);
		index ++;
		while(s->env[index])
		{
			s->env[index] = ft_strdup(s->env[index + 1]);
			index ++;
		}
	}
	else
		s->env[index] = NULL;
}

void unset_env(t_shell *s, char *str)
{
	int len;
	int i;

	i = 0;
	len = ft_strlen(str);
	while(s->env[i])
	{
		printf("%s,%d\n",str,len);
		if(!ft_strncmp(s->env[i],str,len))
		{
			if(s->env[i][len] && s->env[i][len] == '=')
			{
				remove_env(s, i);	
			}
		}
		i ++;
	}
}

void command_unset(t_job *j, t_shell *s)
{
	char **vars;
	int k;
	
	k = 1;
	while(j->args[k])
	{
		unset_env(s, j->args[k]);
		k ++;
	}
}