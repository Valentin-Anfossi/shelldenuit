/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:32:34 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/12 19:32:13 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ms_cmdlst(void)
{
	static char	*cmdlst[8];

	cmdlst[0] = "echo";
	cmdlst[1] = "cd";
	cmdlst[2] = "pwd";
	cmdlst[3] = "export";
	cmdlst[4] = "unset";
	cmdlst[5] = "env";
	cmdlst[6] = "exit";
	cmdlst[7] = NULL;
	return (cmdlst);
}

//Compare 2 strings, return 0 = different 1 = same
int ms_strcmp(char *str1, const char *str2)
{
	int i = 0;
	if(!str1 || !str2)
		return (0);
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if(i == (int)ft_strlen(str1) && i == (int)ft_strlen(str2))
		return (1);
	else
		return (0);
}

int	ms_lstsize(t_token *lst)
{
	t_token	*list;
	int		i;

	list = lst;
	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

void	debug_print_tokens(t_token *tokens)
{
	t_token	*cur_token;

	if (!tokens)
	{
		printf("No token list to print !\n");
		return ;
	}
	cur_token = tokens;
	while (cur_token)
	{
		if (!cur_token->content)
			printf("{%d:NULL}", cur_token->type);
		else
			printf("{%d:%s}", cur_token->type, cur_token->content);
		cur_token = cur_token->next;
	}
	printf("\n");
}


void debug_print_job(t_job *jobs)
{
	t_job *job;
	t_redir *redir;
	int	i = 0;

	job = jobs;
	if (!job)
	{
		ft_printf("No jobs");
		return ;
	}
	while (job)
	{
		redir = job->redir;
		i = 0;
		if (job->error != 0)
			ft_printf("ERROR\n");
		if (job->cmd)
			ft_printf("CMD : %s\n", job->cmd);
		if (job->redir)
		{
			while(redir)
			{
				ft_printf("REDIRTYPE :%d REDIRTARGET: %s\n",redir->type,redir->target);
				redir = redir->next;
			}
		}
		while (job->args[i])
		{
			ft_printf("ARG %d : %s ; ", i, job->args[i]);
			i++;
		}
		if(job->piped_job == NULL)
			break ;
		else
		{
			job = job->piped_job;
			ft_printf("\n");
		}
	}
	ft_printf("\n");
}

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
	out = (char **)malloc(sizeof(char *) * 2);
	out[0] = (char *)malloc(i+2);
	ft_strlcpy(out[0], string, i+1);
	string ++;
	string+=i;
	out[1] = ft_strdup(string);

	return (out);
}

char	*ms_getenv(char *key, t_shell *s)
{
	int		i;
	char	**actual;
	char	*out;

	out = NULL;
	i = 0;
	while (s->env[i])
	{
		actual = ms_split(s->env[i], '=');
		if (actual && ms_strcmp(actual[0], key))
		{
			out = ft_strdup(actual[1]);
			free(actual[0]);
			free(actual[1]);
			free(actual);
			break ;
		}
		else if(actual)
		{
			free(actual[0]);
			free(actual[1]);
			free(actual);
		}
		i++;
	}
	return (out);
}

void	free_shell(t_shell *s)
{
	int i;

	i = 0;
	while(s->env[i])
	{
		free(s->env[i]);
		i ++;
	}
	free(s->env);
	if(s->cwd)
		free(s->cwd);
	free(s);
}

int startswith(char *s, char *start)
{
	int i;

	i = 0;
	if(!s || !start)
		return (0);
	while(start[i])
	{
		if(s[i] != start[i] && s[i])
		{
			return (0);
		}
		i ++;
	}
	return (1);
}

int	is_str_cmd(char *t)
{
	int	i;
	char *s;
	i = 0;

	s = ft_strtrim(t, "\'\"");
	while (ms_cmdlst()[i])
	{
		if (ms_strcmp(ms_cmdlst()[i],s))
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
char **ms_fix_args(t_job *job)
{
	char **args;
	int i;
	int j;

	i = 0;
	j = 0;

	args = (char **)malloc(sizeof(char *) * (ms_charraylen(job->args) + 2));
	i = 0;
	args[j] = ft_strdup(job->cmd);
	j++;
	while(job->args[i])
	{
		if(!ms_strcmp(" ",job->args[i]))
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
	int		j;

	i = 0;
	while (s->env[i])
	{
		j = 0;
		split = ft_split(s->env[i], '=');
		if (ms_strcmp(split[0], env))
		{
			free(s->env[i]);
			tmp = ft_strjoin(split[0], "=");
			s->env[i] = ft_strjoin(tmp, str);
			while(split[j++])
				free(split[j]);
			free(tmp);
			free(split);
			return (1);
		}
		i ++;
	}
	return (0);
}

int ms_isstrinstr(char *s, char *tofind)
{
	int i;
	int j;

	if(!s || !tofind)
		return (0);
	while(s[i])
	{
		while (s[i] == tofind[j])
		{
			i++;
			j++;
		}
		if(j == ft_strlen(tofind) - 1)
			return (1);
		i ++;
	}
	return (0);
}
