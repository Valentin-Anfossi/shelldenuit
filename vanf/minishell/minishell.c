/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:20:00 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/10 17:51:44 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_sigint(int sig)  { 
	printf("Signal : %d\n", sig);
	if(sig == 2)
		printf("Exiting...\n");
	exit(1);
} 

void shell_start(s_shell *shell)
{

	shell->path = getcwd(NULL,0);
	chdir(shell->path);
	shell->path = ft_strjoin(shell->path,"$ ");
}

int shell_execute(char *path)
{
	int ret;
	pid_t f = fork();
	//Faut initialiser Argv avant de le passer a execve (meme si il est vide) sinon execve fail et ne lance rien
	char **argv;
	
    if(f == 0)
    {
        argv = NULL;
        execve(path, argv, NULL);
        perror("Error");
        exit(EXIT_FAILURE);
    }
	else
	{
		waitpid(f,&ret,0);
	}
}

int shell_cd(char *path)
{
	
}

int parse_shell(char *line)
{
	int i = 0;
	while(line[i])
	{
		if(line[i] == '.' && line[i+1] == '/')
			shell_execute(line);
		if(line[i] == 'c' && line[i+1] == 'd')
			shell_cd(line);
		i ++;
	}
}

int main(void)
{
	char *line;
	s_shell *shell;
	shell = (s_shell *)malloc(sizeof(s_shell));
	signal(SIGINT, handle_sigint);
	shell_start(shell);	
	while(1)
	{
		line = readline("minishell $ ");
		add_history(line);
		printf("%s\n",line);
		parse_shell(line);
	}
	printf("\nEnd.\n");
}