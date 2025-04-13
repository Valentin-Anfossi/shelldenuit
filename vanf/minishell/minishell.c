/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:20:00 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/13 19:24:27 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_sigint(int sig)  { 
	printf("Signal : %d\n", sig);
	if(sig == 2)
	{
		rl_on_new_line();
		rl_replace_line("",1);
		rl_redisplay();
		printf("Exiting...\n");
	}
	exit(1);
} 

void shell_start(s_shell *shell)
{
	shell->path = getcwd(NULL,0);
	chdir(shell->path);
}

int main(void)
{
	char *line;
	s_shell *shell;
	s_token **tokens;
	shell = (s_shell *)malloc(sizeof(s_shell));
	char *test_line;
	test_line = "./print_test";
	//signal(SIGINT, handle_sigint);
	shell_start(shell);
	add_history(test_line);
	while(1)
	{
		line = readline("minishell $ ");
		if(line)
			add_history(line);
		tokens = tokenizer_start(line);
		debug_print_tokens(tokens);
	}
	clear_history();
	printf("\nEnd.\n");
}
