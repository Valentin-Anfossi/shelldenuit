/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:20:00 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/10 17:58:57 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// les signaux on verra a la fin
void handle_sigint(int sig)  { 
	printf("Signal : %d\n", sig);
	if(sig == 2)
		printf("Exiting...\n");
	exit(1);
} 

void shell_start(s_shell *shell)
{
	//getcwd (get current working directory)
	shell->path = getcwd(NULL,0);
	//chdir permet de changer le working directory (donc la ca change rien mais spour lexemple)
	chdir(shell->path);
}

int shell_execute(char *path)
{
	int ret;
	pid_t f = fork();
	char **argv;

	// si f(pid du proccess fork) == 0 alors le process est le process enfant
    if(f == 0)
    {
		//Faut initialiser Argv avant de le passer a execve (meme si il est vide) sinon execve fail et ne lance rien
        argv = NULL;
        execve(path, argv, NULL);
		//perror permet de print le message d'erreur renvoye par execve (si le fichier existe pas par ex.)
        perror("Error");
        exit(EXIT_FAILURE);
    }
	// si non, c'est le parent donc on wait que f soit fini
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
	//tu peux regarder readline.c si tu veux mais c simple, ca read, ca ajoute a l'history et a la fin faut clean c tout
	while(1)
	{
		line = readline("minishell $ ");
		add_history(line);
		printf("%s\n",line);
		parse_shell(line);
	}
	printf("\nEnd.\n");
}