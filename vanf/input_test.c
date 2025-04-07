/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 06:08:14 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/07 20:30:13 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h> 
#include <stdlib.h>
#include "input_test.h"

typedef struct t_shell
{
	char *path;
	char *line;
} s_shell;

void handle_sigint(int sig)  { 
	printf("Signal : %d\n", sig);
	exit(1);
} 

void shell_start()
{
	
}

int shell_execute(char *path)
{
	int ret;
	pid_t f = fork();
	//Faut initialiser Argv avant de le passer a execve (meme si il est vide) sinon execve fail et ne lance rien
	char *argv[] = {path, NULL};
	
    if(f == 0)
    {
        char *argv[] = {NULL};
        execve(path, argv, NULL);
        perror("Error");
        exit(EXIT_FAILURE);
    }
	else
	{
		waitpid(f,&ret,0);
	}
}

int parse_shell(char *line)
{
	int i = 0;
	while(line[i])
	{
		if(line[i] == '.' && line[i+1] == '/')
			shell_execute(line);
		i ++;
	}
}

int main(void)
{
	char *line;
	s_shell *shell;
	signal(SIGINT, handle_sigint);
	shell_start();
	while(1)
	{
		line = readline("");
		if(line == NULL)
			printf("Ctrl+D\n");
		else
		{
			parse_shell(line);
		}
	}
	printf("\nEnd.\n");
}