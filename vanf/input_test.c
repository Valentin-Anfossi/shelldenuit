/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 06:08:14 by vanfossi          #+#    #+#             */
/*   Updated: 2025/03/30 04:14:05 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
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
	
	execve(path,NULL,NULL);
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
			printf("Input :\n%s\n",line);
        }
	}
}