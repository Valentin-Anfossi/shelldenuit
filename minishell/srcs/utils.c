/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:41:51 by vanfossi          #+#    #+#             */
<<<<<<< HEAD:minishell/utils.c
<<<<<<< HEAD:minishell/utils.c
/*   Updated: 2025/04/18 03:18:50 by vanfossi         ###   ########.fr       */
=======
/*   Updated: 2025/04/24 10:24:59 by vanfossi         ###   ########.fr       */
>>>>>>> 80bda5a (Creation de job ATESTER):minishell/srcs/utils.c
=======
/*   Updated: 2025/04/22 05:24:04 by vanfossi         ###   ########.fr       */
>>>>>>> ba9bfb06332e120b263b3dc0dd61a48dcaed5752:minishell/srcs/utils.c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD:minishell/utils.c
//Return last token from lst
t_token	*token_last(t_token *lst)
{
	t_token	*list;

<<<<<<< HEAD:minishell/utils.c
	if (!lst)
		return (0);
	list = lst;
	while (list->next)
		list = list->next;
	return (list);
}

//Add token to the back of lst
void	token_add_back(t_token **lst, t_token *token)
{
	t_token	*last;

	if (!lst || !token)
		return ;
	if (*lst == 0)
		*lst = token;
	else
	{
		last = token_last(*lst);
		last->next = token;
	}
}
=======
char **ms_cmdlst()
{
	char **cmdlst;
	cmdlst = (char **)malloc(sizeof(char *) * 8);
>>>>>>> 80bda5a (Creation de job ATESTER):minishell/srcs/utils.c

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
int ms_strcmp(char *str1, char *str2)
{
	int i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if(i == (int)ft_strlen(str1) && i == (int)ft_strlen(str2))
		return (1);
	else
		return (0);
=======
//Compare 2 strings, return 0 if theyre the same
int	ms_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
>>>>>>> ba9bfb06332e120b263b3dc0dd61a48dcaed5752:minishell/srcs/utils.c
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

<<<<<<< HEAD:minishell/utils.c
void debug_print_job(t_job *jobs)
{
<<<<<<< HEAD:minishell/utils.c
	t_job *job;
	int	i = 0;
=======
	int	i;
	t_job *job;
>>>>>>> 80bda5a (Creation de job ATESTER):minishell/srcs/utils.c
=======
void	debug_print_job(t_job **jobs)
{
	t_job	*job;
	int		i;
>>>>>>> ba9bfb06332e120b263b3dc0dd61a48dcaed5752:minishell/srcs/utils.c

	job = jobs;
	if (!job)
	{
		ft_printf("No jobs");
		return ;
	}
	while (job)
	{
<<<<<<< HEAD:minishell/utils.c
<<<<<<< HEAD:minishell/utils.c
		ft_printf("ARG %d : %s ; ", i, job->args[i]);
		i++;
=======
=======
>>>>>>> ba9bfb06332e120b263b3dc0dd61a48dcaed5752:minishell/srcs/utils.c
		i = 0;
		if (job->error != 0)
			ft_printf("ERROR\n");
		if (job->cmd)
			ft_printf("CMD : %s\n", job->cmd);
<<<<<<< HEAD:minishell/utils.c
		if (job->redir)
		{
			while(job->redir)
			{
				ft_printf("REDIRTYPE :%d REDIRTARGET: %s\n",job->redir->type,job->redir->target);
				job->redir = job->redir->next;
			}
		}
=======
>>>>>>> ba9bfb06332e120b263b3dc0dd61a48dcaed5752:minishell/srcs/utils.c
		while (job->args[i])
		{
			ft_printf("ARG %d : %s ; ", i, job->args[i]);
			i++;
		}
<<<<<<< HEAD:minishell/utils.c
		if(job->piped_job == NULL)
=======
		if (job->piped_job == NULL)
>>>>>>> ba9bfb06332e120b263b3dc0dd61a48dcaed5752:minishell/srcs/utils.c
			break ;
		else
		{
			job = job->piped_job;
			ft_printf("\n");
		}
<<<<<<< HEAD:minishell/utils.c
>>>>>>> 80bda5a (Creation de job ATESTER):minishell/srcs/utils.c
=======
>>>>>>> ba9bfb06332e120b263b3dc0dd61a48dcaed5752:minishell/srcs/utils.c
	}
	ft_printf("\n");
}
