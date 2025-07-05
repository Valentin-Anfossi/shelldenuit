/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:20:30 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/05 02:50:16 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ms_command_export(t_job *j, t_shell *s)
{
    int i = 1;
    int status = 0;
    int check;

    if (!j->args[1]) 
        return (ms_print_exported_vars(s));
    while (j->args[i]) 
	{
        check = ms_check_export(j->args[i]);
        if (check == 1) 
		{
            ms_export_error(j->args[i]);
            status = 1;
        }
        else if (check == 0) 
		{
            if (ms_export_valid(j->args[i], s) != 0)
				status = 1;
		}
		else if(check == 2)
			status = 0;
		i++;
    }
    return status;
}

int ms_export_add(t_shell *s, char *add_env)
{
    int count;
	int i;
    char **new_env;

	count = 0;
	i = 0;
    while (s->env[count])
	{
        count++;	
	}
	new_env = (char **)malloc(sizeof(char *) * (count + 2));
    while (i < count) 
	{
        new_env[i] = ft_strdup(s->env[i]);
		i ++;
	}
    new_env[count] = ft_strdup(add_env);
    new_env[count + 1] = NULL;
    ms_free_env(s->env);
    s->env = new_env;
    return 0;
}

int ms_check_export(char *str)
{
	int i;

	i = 0;
	if(!str || !str[0])
		return (1);
	if(!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	i = 1;
	while(str[i] && str[i] != '=')
	{
		if(!ft_isalnum(str[i]) && str[i] != '_')
			return(1);
		i ++;
	}
	if(!ft_strchr(str,'='))
		return(2);
	return (0);
}
int ms_export_error(char *str)
{
	ft_putstr_fd("☠️  MinisHell: export: '",STDERR_FILENO);
	ft_putstr_fd(str,STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n",STDERR_FILENO);
	return (1);
}
int ms_print_exported_vars(t_shell *s)
{
	(void)s;
	return (0);
}