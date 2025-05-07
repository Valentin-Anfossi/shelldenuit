/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:47:44 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/29 14:47:44 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int check_export(t_job *job, t_shell *s)
// {
// 	int i;
// 	int j;
// 	char *bef;
// 	char *aft;

// 	i = 0;
// 	j = 0;
// 	while(job->args[i])
// 	{
// 		while(job->args[i][j] != '=')
// 		{
// 			if (!ft_isalnum(job->args[i][j]) || job->args[i][j] != '_')
// 				return (0);
// 			else
// 				j++;
// 		}
// 		j = 0;
// 		i ++;
// 	}
// 	return (1);
// }

void command_env(t_shell *shell)
{
	int i;

	i = 0;
	while(shell->env[i])
	{
		ft_printf("%s\n",shell->env[i]);
		i ++;
	}
}

int check_export(char **vars, t_shell *shell, char *str)
{
	int i;

	i = 0;
	if(vars[0] && vars[1])
	{
		// while(shell->env[i])
		// {
		// 	if(getenv(vars[0]))
		// 	{
		// 		ft_printf("MODIF VARIABLE");
		// 		*getenv(vars[0]) = str;
		// 		return (0);
		// 	}
		// 	i ++;
		// }
		i = 1;
		if(!ft_isalpha(vars[0][0]))
			return (0);
		while(vars[0][i])
		{
			if(!ft_isalnum(vars[0][i]) && vars[0][i] != '_')
				return (0);
			i ++;
		}
	}
	return (1);
}

// le nom de la var d'env doit etre ALPHANUM OU UNDERSCORE
// le contenu = n'importe quoi
// faut check si y'a un espace
// modifier si elle existe deja
//	MAJ ou min, underscore
void	command_export(t_job *j, t_shell *s)
{
	char **vars;
	int i;
	int k;

	i = 0;
	k = 1;
	// if (!check_export(j, s))
	// 	return ;
	while (s->env[i])
	{
		printf("%d\n",&s->env[i]);
		i ++;
	}
	while (j->args[k])
	{
		vars = ms_split(j->args[k],'=');
		if(check_export(vars,s,j->args[k]))
		{
			printf("%d\n",&s->env[i-1]);
			s->env[i-1] = ft_strdup(j->args[k]);
			i ++;
			s->env[i] = NULL;
			ft_printf("%d",check_export(vars,s,j->args[k]));
		}
		else
		{
			
		}
		k ++;
	}
}

void	command_echo(t_job *j, t_shell *s)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (ms_strcmp(j->args[i], " "))
		i++;
	while (j->args[i])
	{
		if (ms_strcmp(j->args[i], "-n"))
		{
			n = 1;
			i ++;
			continue ;
		}
		ft_printf("%s", j->args[i]);
		i ++;
		// if (j->args[i])
		// 	ft_printf(" ");
	}
	if (!n)
		ft_printf("\n");
}
void	command_cd(t_job *j, t_shell *s)
{
	if (j->args[1])
	{
		perror("cd: too many arguments");
		return ;
	}
	if (opendir(j->args[0]))
	{
		
	}
}


void	select_command(t_job *jobs, t_shell *s)
{
	if (jobs->cmd)
	{
		if (ms_strcmp(jobs->cmd, "echo"))
			command_echo(jobs, s);
		if (ms_strcmp(jobs->cmd, "env"))
			command_env(s);
		if (ms_strcmp(jobs->cmd, "export"))
			command_export(jobs, s);
		if (ms_strcmp(jobs->cmd, "cd"))
			command_cd(jobs, s);
	}
}
// void select_command(t_job *job)
// {
// 	char *cmd;

// 	cmd = ft_strtrim(job->cmd,"\'\"");
// 	if(ms_strcmp("cd",cmd))
// 		cmd_cd(job);
// 	else if(ms_strcmp("echo",cmd))
// 		cmd_echo(job);
// 	else if(ms_strcmp("pwd",cmd))
// 		cmd_pwd(job);
// 	else if(ms_strcmp("export",cmd))
// 		cmd_export(job);
// 	else if(ms_strcmp("unset",cmd))
// 		cmd_unset(job);
// 	else if(ms_strcmp("env",cmd))
// 		cmd_env(job);
// 	else if(ms_strcmp("exit",cmd))
// 		cmd_exit(job);
// 	else
// 		is_str_exec(job);
// }

// void is_str_exec(job)
// {
// 	// check si y a un file de merde
// 	ft_printf("error");
// }


// void cmd_exec(t_job *job)
// {

// }
