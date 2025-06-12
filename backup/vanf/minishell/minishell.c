/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:20:00 by vanfossi          #+#    #+#             */
/*   Updated: 2025/05/28 14:39:59 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{ 
	printf("Signal : %d\n", sig);
	if (sig == 2)
	{
		rl_on_new_line();
	//	rl_replace_line("",1);
		rl_redisplay();
		printf("Exiting...\n");
	}
	exit(1);
} 

void	shell_start(s_shell *shell)
{
	shell->path = getcwd(NULL,0);
	chdir(shell->path);
}

int	main(void)
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
		if (line)
			add_history(line);
		tokens = tokenizer_start(line);
		//debug_print_tokens(tokens);
		if (check_tokens_list(tokens))
		{
			delete_tokens(tokens);
			continue;	
		}
		//create_jobs(tokens);
		
		
		delete_tokens(tokens);
	}
	clear_history();
	printf("\nEnd.\n");
}

int check_tokens_list(s_token **tokens)
{
	s_token *cur_token;
	int list_length;

	list_length = ms_lstsize(*tokens);
	cur_token = *tokens;
	if (tokens[0]->type == 2)
		return (ft_printf("%s: command not found\n",tokens[0]->content));
	while (cur_token)
	{
		if (cur_token->type > 2 && cur_token->type < 7 && !cur_token->content)
		{
			errno = 5;
			if (!cur_token->next)
				return (write(2,"minishell : syntax error near unexpected token 'newline'\n",58));
			else
				cur_token = cur_token->next;
			if (cur_token->type > 2 && cur_token->type < 7)
				return(write(2,"minishell : syntax error near unexpected token ",48) 
			+ write(2,get_error(cur_token->type),ft_strlen(get_error(cur_token->type))));
		}
		cur_token = cur_token->next;
	}
	return (0);
}

char *get_error(int type)
{
	if (type == 3)
		return ("<\n");
	if (type == 4)
		return (">\n");
	if (type == 5)
		return ("<<\n");
	if (type == 6)
		return (">>\n");
}

void create_jobs(s_token **tokens)
{
	int job_id;
	s_token *cur;
	
	job_id = 0;	
	cur = *tokens;

	while(*tokens)
	{
		s_job *new_job;
		new_job = (s_job *)malloc(sizeof(s_job));
		while(cur->type != 7)
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
