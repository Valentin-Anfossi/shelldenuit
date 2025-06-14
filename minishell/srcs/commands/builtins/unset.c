/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:25:00 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/14 10:57:17 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ms_remove_env(t_shell *s, int index)
{
    free(s->env[index]);
    while (s->env[index + 1])
    {
        s->env[index] = s->env[index + 1];
        index++;
    }
    s->env[index] = NULL;
}

int ms_unset_env(t_shell *s, char *str)
{
    int len;
    int i;

    if (!str || !*str)
        return (0);
    len = ft_strlen(str);
    i = 0;
    while (s->env[i])
    {
        if (ft_strncmp(s->env[i], str, len) == 0 && s->env[i][len] == '=')
        {
            ms_remove_env(s, i);
            return (1);
        }
        i++;
    }
    return (0);
}

int ms_command_unset(t_job *j, t_shell *s)
{
    int k;
    int status;

    if (!j->args[1])
        return (0);

    status = 0;
    k = 1;
    while (j->args[k])
    {
        if (!ms_is_valid_var_name(j->args[k]))
        {
            ft_putstr_fd("unset: `", STDERR_FILENO);
            ft_putstr_fd(j->args[k], STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
            status = 1;
        }
        else if (ms_unset_env(s, j->args[k]))
            status = 0;
        k++;
    }
    return (status);
}

int ms_is_valid_var_name(char *str)
{
    if (!str || !*str)
        return (0);
    if (!ft_isalpha(*str) && *str != '_')
        return (0);
    while (*++str)
    {
        if (!ft_isalnum(*str) && *str != '_')
            return (0);
    }
    return (1);
}


// void	remove_env(t_shell *s, int index)
// {
// 	if (s->env[index + 1])
// 	{
// 		s->env[index] = ft_strdup(s->env[index + 1]);
// 		index ++;
// 		while (s->env[index])
// 		{
// 			s->env[index] = ft_strdup(s->env[index + 1]);
// 			index ++;
// 		}
// 	}
// 	else
// 		s->env[index] = NULL;
// }

// int	unset_env(t_shell *s, char *str)
// {
// 	int	len;
// 	int	i;

// 	i = 0;
// 	len = ft_strlen(str);
// 	while (s->env[i])
// 	{
// 		if (!ft_strncmp(s->env[i], str, len))
// 		{
// 			if (s->env[i][len] && s->env[i][len] == '=')
// 			{
// 				remove_env(s, i);
// 				return (1);
// 			}
// 		}
// 		i ++;
// 	}
// 	return (0);
// }

// int	command_unset(t_job *j, t_shell *s)
// {
// 	int		k;

// 	k = 1;
// 	while (j->args[k])
// 	{
// 		if (unset_env(s, j->args[k]))
// 			return (0);
// 		k ++;
// 	}
// 	return (0);
// }
