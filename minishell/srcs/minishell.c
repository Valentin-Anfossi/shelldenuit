/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:33:10 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/02 01:57:17 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exitcode;

//Closes MS if CTRL+D (EOF) is pressed on empty line
void ms_signal_eof(t_shell *s)
{
	free_shell(s);
	clear_history();
	//printf("Exiting Minishell, Bye !\n");
	exit(g_exitcode);
}

int	main(void)
{
	t_shell	*shell;
	char	*line;
	t_token	**tokens;
	t_job	*jobs;

	shell = create_shell();
	handle_signals();
	g_exitcode = 0;
	while (1)
	{
		// if(isatty(fileno(stdin)))
			line = readline("☠️  MinisHell: ");
		// else
		// {
		// 	line = get_next_line(fileno(stdin));
		// }
		if(!line)
			ms_signal_eof(shell);
		// if(ms_strcmp(line,"echo hi >         ./outfiles/outfile01 bye"))
		// 	printf("wooo");
		tokens = ms_tokens(line,shell);
		if(!tokens)
		{
			free(line);
			continue;
		}
		// ms_free_tokens(tokens);
		//printf("Line :(%s)",line);
		free(line);
		// ms_debug_print_tokens(tokens);
		jobs = create_job(tokens);
		free_tokens(tokens);
		//debug_print_job(jobs);
		// if (!check_jobs(jobs))
		ms_execute_jobs(jobs, shell);
		free_jobs(jobs);
	}
	clear_history();
}
