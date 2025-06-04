/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:33:10 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/29 13:36:35 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_pid;

t_shell	*create_shell(void)
{
	extern char	**environ;
	t_shell		*s;
	pid_t		pid_main;
	int			i;

	pid_main = getpid();
	i = 0;
	s = (t_shell *)malloc(sizeof(t_shell));
	s->cwd = NULL;
	while (environ[i])
		i++;
	s->env = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	s->mainpid = pid_main;
	while (environ[i])
	{
		s->env[i] = ft_strdup(environ[i]);
		i++;
	}
	s->env[i] = NULL;
	s->cwd = getcwd(s->cwd, PATH_MAX);
	s->exit_code = 0;
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

void	tokens_start(t_token **t, t_shell *s)
{
	typing_tokens(t);
	check_env(t, s);
	check_tokens(t);
	//debug_print_tokens(tokens);
}

int	main(void)
{
	t_shell	*shell;
	char	*line;
	t_token	**tokens;
	t_job	*jobs;

	shell = create_shell();
	while (1)
	{
		handle_signals();
		line = readline("☠️  Minishell: ");
		if (line[0])
		{
			tokens = create_lst_tokens(line);
			add_history(line);
		}
		else
			continue ;
		tokens_start(tokens, shell);
	//	debug_print_tokens(tokens);
		jobs = create_job(tokens);
	//	debug_print_job(jobs);
		if (!check_jobs(jobs, shell))
			execute_jobs(jobs, shell);
		//debug_print_job(jobs);
		free_jobs(jobs);
		free(line);
		//exit(0);
	}
	clear_history();
}
