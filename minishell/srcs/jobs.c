/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 05:11:05 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/24 11:04:19 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_tok_redir(t_token *t)
{
	if(!t->content)
		return (0);
	else if(ms_strcmp(t->content,">"))
		return (1);
	else if (ms_strcmp(t->content,">>"))
		return (1);
	else if (ms_strcmp(t->content,"<"))
		return (1);
	else if (ms_strcmp(t->content,"<<"))
		return (1);
	else
		return (0);
}

int is_tok_arg(t_token *t)
{
	if(!t)
		return (0);
	if(!is_tok_redir(t) && !is_tok_cmd(t) && !is_tok_pipe(t))
		return (1);
	else
		return (0);
}

int is_tok_exec(t_token *t)
{
	char *s;
	int i;

	i = 0;
	if(t->content)
	{
		s = ft_strtrim(t->content,"\"\'");
		while(s[i] == ' ')
			i ++;
		while(s[i] == '.')
			i ++;
		if(s[i] == '/')
			return (1);
		else
			return (0);
	}
}
int is_tok_cmd(t_token *t)
{
	int i;
	
	i = 0;
	while(ms_cmdlst()[i])
	{
		if(ms_strcmp(ms_cmdlst()[i],ft_strtrim(t->content,"\'\"")))
			return (1);
		else if(is_tok_exec(t))
			return (1);
		i ++;
	}
	return (0);
}
int is_tok_pipe(t_token *t)
{
	if(ms_strcmp(t->content,"|"))
		return (1);
	else
		return (0);
}

t_token *add_to_job_redir(t_token *t, t_job *j)
{
	t_redir *new_redir;
	t_redir *cur_redir;
	
	new_redir = (t_redir *)ft_calloc(sizeof(t_redir),1);
	new_redir->type = get_redir_type(t);
	if(!j->redir)
		j->redir = new_redir;
	else
	{
		cur_redir = j->redir;
		while (cur_redir->next)
			cur_redir = cur_redir->next;
		cur_redir->next = new_redir;
	}
	if(t->next)
	{
		new_redir->target = t->next->content;
		new_redir->next = NULL;
		t = t->next->next;
		return (t);
	}
	else if(!j->error)
		j->error = ERR_NEWLINE;
	return (t);	
}

t_token *add_to_job_cmd(t_token *t, t_job *j)
{
	j->cmd = ft_strtrim(t->content,"\'\"");
	t = t->next;
	return (t);
}

t_token *add_to_job_arg(t_token *t, t_job *j)
{
	int i;
	
	i = 0;
	if(!j->args[0])
	{
		j->args[0] = ft_strdup(t->content);
		j->args[1] = NULL;
		return (t->next);
	}
	while(j->args[i])
		i ++;
	j->args[i] = ft_strdup(t->content);
	j->args[i+1] = NULL;
	return (t->next);
}


t_job *create_job(t_token **tokens)
{
	t_token *t;
	t_job *j;

	j = malloc_job();
	t = *tokens;
	while(t)
	{
		if(is_tok_redir(t))
			if(is_tok_arg(t->next))//on peut faire ca ??
				t = add_to_job_redir(t,j);
			else
			{
				j->error = ERR_NEWLINE;
				break;
			}
		else if(is_tok_cmd(t) && !j->cmd)
		{
			t = add_to_job_cmd(t, j);
		}
		else if(is_tok_pipe(t))
		{
			t = t->next;
			j ->piped_job = create_job(&t);
			break;
		}
		else
			t = add_to_job_arg(t ,j);
	}
	return (j);
}
