/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:32:34 by vanfossi          #+#    #+#             */
/*   Updated: 2025/05/14 05:46:03 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ms_cmdlst()
{
	char **cmdlst;
	cmdlst = (char **)malloc(sizeof(char *) * 8);

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

void	debug_print_tokens(t_token **tokens)
{
	t_token	*cur_token;

	if (!tokens)
	{
		printf("No token list to print !\n");
		return ;
	}
	cur_token = *tokens;
	while (cur_token)
	{
		if (!cur_token->content)
			printf("{Type:%d} ", cur_token->type);
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
	out = malloc(sizeof(char **));
	out[0] = malloc(i+2);
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
			out = actual[1];
			break ;
		}
		i++;
	}
	//free(actual);
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
	free(s);
}

int startswith(char *s, char *start)
{
	int i;

	i = 0;
	if(!s || !start)
		return (NULL);
	while(start[i])
	{
		if(s[i] != start[i] && s[i])
		{
			return (NULL);
		}
		i ++;
	}
	return (1);
}

int	is_str_cmd(char *t)
{
	int	i;

	i = 0;
	while (ms_cmdlst()[i])
	{
		if (ms_strcmp(ms_cmdlst()[i], ft_strtrim(t, "\'\"")))
			return (1);
		else if (is_str_exec(t))
			return (1);
		i ++;
	}
	return (0);
}
