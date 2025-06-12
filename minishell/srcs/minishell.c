/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:33:10 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/12 22:42:02 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exitcode;

//Closes MS if CTRL+D (EOF) is pressed on empty line
void ms_signal_eof(t_shell *s)
{
	free_shell(s);
	clear_history();
	printf("Exiting Minishell, Bye !\n");
	exit(g_exitcode);
}

int ms_tokens_check(t_token *t, t_shell *s)
{
	
}

t_token *ms_tokens(char *line, t_shell *s)
{
	t_token *t;

	if (ft_strlen(line) == 0)
		return (NULL);
	t = ms_lst_tokens(line);
	typing_tokens(t);
	check_env(t,s);
	if(!ms_tokens_check(t))
	{
		free_tokens(t);
		return (NULL);
	}
	debug_print_tokens(tokens);
	add_history(line);
	return (t);
}

int	main(void)
{
	t_shell	*shell;
	char	*line;
	t_token	*tokens;
	t_job	*jobs;

	shell = create_shell();
	handle_signals();
	while (1)
	{
		line = readline("☠️  MinisHell: ");
		if(!line)
			ms_signal_eof(shell);
		tokens = ms_tokens(line,shell);
		if(!tokens)
		{
			free(line);
			continue;
		}
		debug_print_tokens(tokens);
		jobs = create_job(tokens);
		free_tokens(tokens);
		//free(tokens);
		// debug_print_job(jobs);
		// if (!check_jobs(jobs, shell))
		// 	execute_jobs(jobs, shell);
		// free_jobs(jobs);
		// free(line);
	}
	clear_history();
}
