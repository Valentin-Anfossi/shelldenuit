/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:20:00 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/14 18:09:10 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	//	rl_replace_line("",1);
void	handle_sigint(int sig)
{
	printf("Signal : %d\n", sig);
	if (sig == 2)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("Exiting...\n");
	}
	exit(1);
}

void	shell_start(t_shell *shell)
{
	shell->path = getcwd(NULL, 0);
	chdir(shell->path);
}

	//signal(SIGINT, handle_sigint);
		//create_jobs(tokens);
int	main(void)
{
	char	*line;
	t_shell	*shell;
	t_token	**tokens;
	char	*test_line;

	shell = (t_shell *)malloc(sizeof(t_shell));
	shell_start(shell);
	while (1)
	{
		line = readline("minishell $ ");
		if (line)
			add_history(line);
		tokens = tokenizer_start(line);
		debug_print_tokens(tokens);
		if (check_tokens_list(tokens))
		{
			delete_tokens(tokens);
			continue ;
		}
		delete_tokens(tokens);
	}
	clear_history();
	printf("\nEnd.\n");
}

char	*get_error(int type)
{
	if (type == 3)
		return ("<\n");
	if (type == 4)
		return (">\n");
	if (type == 5)
		return ("<<\n");
	if (type == 6)
		return (">>\n");
	else
		return ("il faut return un truc");
}

void	create_jobs(t_token **tokens)
{
	int		job_id;
	t_token	*cur;

	job_id = 0;
	cur = *tokens;
	while (*tokens)
	{
		t_job	*new_job;
		new_job = (t_job *)malloc(sizeof(t_job));
		while (cur->type != 7)
		{
			if (cur->type == 1)
			{
				new_job->command = 1;
				new_job->exec_path = cur->content;
			}
			if (cur->type == 3)
			{
				new_job->infile_path = cur->content;
			}
		}
	}
}
