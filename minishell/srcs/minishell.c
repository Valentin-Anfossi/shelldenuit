/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:33:10 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/07 23:56:01 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exitcode;

void	ms_signal_eof(t_shell *s)
{
	free_shell(s);
	ft_putstr_fd("exit\n", STDERR_FILENO);
	clear_history();
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
		line = readline("☠️  MinisHell: ");
		if (!line)
			ms_signal_eof(shell);
		tokens = ms_tokens(line, shell);
		if (!tokens)
		{
			free(line);
			continue ;
		}
		free(line);
		jobs = create_job(tokens);
		free_tokens(tokens);
		ms_execute_jobs(jobs, shell);
		free_jobs(jobs);
	}
}
