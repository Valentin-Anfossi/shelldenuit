/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:33:10 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/12 16:38:01 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exitcode;

t_shell	*create_shell(void)
{
	extern char	**environ;
	t_shell		*s;
	int			i;

	i = 0;
	s = (t_shell *)malloc(sizeof(t_shell));
	s->cwd = NULL;
	while (environ[i])
		i++;
	s->env = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (environ[i])
	{
		s->env[i] = ft_strdup(environ[i]);
		i++;
	}
	s->env[i] = NULL;
	s->cwd = getcwd(s->cwd, PATH_MAX);
	g_exitcode = 0;
	return (s);
}

int	is_tok_quoted(t_token *tok)
{
	if (tok->content[0] == '\''
		&& tok->content[ft_strlen(tok->content)] == '\'')
		return (1);
	else
		return (0);
}

int	verif_tokens(t_token *token)
{
	t_token *t;

	t = token;
	printf("veriftokens\n");
	while(t)
	{
		if(is_tok_redir(t))
		{
			while(t->next && t->next->type == 0)
				t = t->next;
			if(t->next && (!is_tok_arg(t->next) || is_tok_redir(t->next)))
			{
				printf("Minishell: syntax error near unexpected token '%s'\n",t->next->content);
				return (1);
			}
			else if (!t->next)
			{
				printf("Minishell: syntax error near unexpected token `newline'\n");
				return (1);
			}
		}
		t = t->next;
	}
	return (0);
}

int	tokens_start(t_token **t, t_shell *s)
{
	if (!*t)
	{
		return (1);
	}
	if (!(*t)->next && (ms_strcmp((*t)->content,"!") || ms_strcmp((*t)->content,":")))
		return (1);
	typing_tokens(t);
	check_env(t, s);
	debug_print_tokens(t);
	check_tokens(t);
	return (verif_tokens(*t));
	return (0);
}

int	main(void)
{
	t_shell	*shell;
	char	*line;
	t_token	**tokens;
	t_job	*jobs;

	shell = create_shell();
	handle_signals();
	while (1)
	{
		// signal_parent_sigaction();
		// signal(SIGQUIT,&signal_sigquit);
		line = readline("☠️  MinisHell: ");
		if(!line)
		{
			printf("exit\n");
			exit(g_exitcode);
		}
		if (ft_strlen(line) > 0)
		{
			printf("debut tokens\n");
			tokens = create_lst_tokens(line);
			debug_print_tokens(tokens);
			add_history(line);
		}
		else
		{
			free(line);
			line = NULL;
			continue ;
		}
		printf("end create tokens\n");
		if (tokens_start(tokens, shell))
		{
			free(line);			
			free_tokens(tokens);
			continue;
		}
		debug_print_tokens(tokens);
		jobs = create_job(tokens);
		free_tokens(tokens);
		//free(tokens);
		debug_print_job(jobs);
		if (!check_jobs(jobs, shell))
			execute_jobs(jobs, shell);
		//debug_print_job(jobs);
		free_jobs(jobs);
		free(line);
		//exit(0);
	}
	clear_history();
}
