/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:20:30 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/13 23:42:18 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ms_command_export(t_job *j, t_shell *s)
{
    int i = 1;
    int status = 0;
    int check;

    if (!j->args[1]) 
	{
        ms_print_exported_vars(s);
        return 0;
    }
    while (j->args[i]) 
	{
        check = ms_check_export(s, j->args[i]);
        if (check == 1) 
		{
            ms_export_error(j->args[i]);
            status = 1;
        }
        else if (check == 0) 
            if (ms_export_valid(j->args[i], s) != 0)
                status = 1;
		else if(check == 2)
			status = 0;
		i++;
    }
    return status;
}
int ms_export_valid(char *str, t_shell *s)
{
    char *eq_pos;
    size_t name_len;
    int i;
	
	i = 0;
	eq_pos = ft_strchr(str, '=');
	if(eq_pos)
		name_len = (size_t)(eq_pos - str);
    else
        name_len = ft_strlen(str);
    while (s->env[i]) 
	{
        if (ft_strncmp(s->env[i], str, name_len) == 0 && 
            s->env[i][name_len] == '=') {
            free(s->env[i]);
            if (!(s->env[i] = ft_strdup(str)))
                return 1;
            return 0;
        }
        i++;
    }
    return ms_export_add(s, str);
}

int ms_export_add(t_shell *s, char *add_env)
{
    int count;
	int i;
    char **new_env;

	count = 0;
	i = 0;
    while (s->env[count])
        count++;
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

void ms_free_env(char **env)
{
	int i = 0;
    if (!env) return;
    while (env[i])
	free(env[i++]);
    free(env);
}
// 0=OK 1=invalid name 2=do nothing
int ms_check_export(t_shell *s, char *str)
{
	int i;
	int ret;

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
	return (0);
}


// int ms_command_export(t_job *j, t_shell *s)
// {
// 	int check;
// 	int i;
	
// 	i = 1;
// 	if(!j->args[1])
// 		return(ms_export_print(s));
// 	while(j->args[i])
// 	{
// 		check = ms_check_export(s,j->args[i]);
// 		if(check == 1)
// 			return(ms_export_error(j->args[i]));
// 		if(check == 2)
// 			return (0);
// 		if(check == 0)
// 			return(ms_export_valid(j->args[i],s));
// 		i++;
// 	}
// 	return (0);
// }
// int	ms_export_print(t_shell *s)
// {

// }
// int ms_export_valid(char *str, t_shell *s)
// {
// 	int i;

// 	i = 0;
// 	while(s->env[i])
// 	{
// 		if(ft_strncmp(s->env[i], str, ft_strlen(str)) != 0)
// 			if(s->env[i][ft_strlen(str) + 1] == '=')
// 				{
// 					free(s->env[i]);
// 					s->env[i] = ft_strdup(str);
// 					return (0);
// 				}
// 	}
// 	ms_export_add(s,str);
// }



// void	ms_export_add(t_shell *s, char *add_env)
// {
// 	int		i;
// 	int		j;
// 	char	**new_env;

// 	j = 0;
// 	i = 0;
// 	while (s->env[i])
// 		i++;
// 	new_env = malloc(sizeof(char *) * (i + 2));
// 	i = 0;
// 	while (s->env[i])
// 	{
// 		new_env[i] = ft_strdup(s->env[i]);
// 		i++;
// 	}
// 	new_env[i] = ft_strdup(add_env);
// 	new_env[i + 1] = NULL;
// 	while (s->env[j])
// 	{
// 		free(s->env[j]);
// 		j++;
// 	}
// 	free(s->env);
// 	s->env = new_env;
// }

// void	modif_export(t_shell *s, char *vars, char *newstr)
// {
// 	int	i;

// 	i = 0;
// 	while (ft_strncmp(s->env[i], vars, ft_strlen(vars)) != 0)
// 		i++;
// 	free(s->env[i]);
// 	s->env[i] = ft_strdup(newstr);
// }

// int	command_export(t_job *j, t_shell *s)
// {
// 	char	**vars;
// 	int		k;
// 	int		check;

// 	k = 1;
// 	while (j->args[k])
// 	{
// 		vars = ms_split(j->args[k], '=');
// 		check = check_export(vars, s, j->args[k]);
// 		if (check == 2)
// 		{
// 			modif_export(s, vars[0], j->args[k]);
// 			ms_free_split(vars);
// 			return (0);
// 		}
// 		else if (check == 0 && vars)
// 		{
// 			add_to_env(s, j->args[k]);
// 			ms_free_split(vars);
// 			return (0);
// 		}
// 		k ++;
// 	}
// 	ms_free_split(vars);
// 	return (1);
// }

// void ms_free_split(char **split)
// {
// 	int i;

// 	i = 0;
// 	if(!split || !split[0])
// 		return ;
// 	while(split[i])
// 	{
// 		free(split[i]);
// 		i ++;
// 	}
// 	free(split);
// }
