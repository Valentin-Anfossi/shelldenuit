/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:20:00 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/11 16:39:50 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// les signaux on verra a la fin
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

int shell_testoutfile(char *path)
{
	int ret;
	int pipedes[2];
	char read_buffer;
	pipe(pipedes);
	pid_t f=fork();
	int bytes_read;
	//Cree le pipe 
	
	if(f == 0)
	{
		
		close(pipedes[0]);
		dup2(pipedes[1],1);
		//duplique le stdout(1) du process vers la write end du pipe pipedes[1])
		// if(dup2(pipedes[1],1)== -1)
		// {
		// 	perror("duperror");
		// }
		//dup2(pipedes[1],2);
		//close(pipedes[1]);
		char *argv[] = {path,NULL};
		execve(path, argv, NULL);
		perror("Execve Error");
		exit(EXIT_FAILURE);
	}
	else
	{
		close(pipedes[1]);
		while (read(pipedes[0], &read_buffer, 1) > 0)
		{
			printf("%c/",read_buffer);
		}
		waitpid(f,&ret,0);
		//close(pipedes[0]);
	}
}

int shell_cd(char *path)
{
	
}

int parse_shell(char *line)
{
	int i = 0;
	if(!line)
	{
		printf("Ctrl+D Exiting...\n");
		rl_clear_history();
		exit(0);
	}
	while(line[i])
	{
		if(line[i] == '.' && line[i+1] == '/')
			shell_testoutfile(line);
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
	char *test_line;
	test_line = "./print_test";
	//signal(SIGINT, handle_sigint);
	shell_start(shell);
	add_history(test_line);
	//tu peux regarder readline.c si tu veux mais c simple, ca read, ca ajoute a l'history et a la fin faut clean c tout
	while(1)
	{
		line = readline("minishell $ ");
		if(line)
		{
			add_history(line);
			//printf("%s\n",line);
		}
		parse_shell(line);
	}
	printf("\nEnd.\n");
}


// int main(int argc, char *argv[])
// {
// 	int    pipefd[2];
// 	char   buf;
// 	pid_t  cpid;

// 	if (argc != 2) {
// 		fprintf(stderr, "Usage: %s <string>\n", argv[0]);
// 		exit(EXIT_FAILURE);
// 	}

// 	if (pipe(pipefd) == -1)
// 		err(EXIT_FAILURE, "pipe");

// 	cpid = fork();
	
// 	if (cpid == 0) 
// 	{    /* Child reads from pipe */
// 		if (close(pipefd[1]) == -1)  /* Close unused write end */
// 			err(EXIT_FAILURE, "close");
// 		while (read(pipefd[0], &buf, 1) > 0)
// 			write(1, &buf, 1);
// 		close(pipefd[0]);
// 	}
	
// 	else {            /* Parent writes argv[1] to pipe */
// 		if (close(pipefd[0]) == -1)  /* Close unused read end */
// 			err(EXIT_FAILURE, "close");
// 		if (write(pipefd[1], argv[1], strlen(argv[1])) != strlen(argv[1]))
// 			err(EXIT_FAILURE, "write");
// 		if (close(pipefd[1]) == -1)  /* Reader will see EOF */
// 			err(EXIT_FAILURE, "close");
// 		if (wait(NULL) == -1)        /* Wait for child */
// 			err(EXIT_FAILURE, "wait");
// 		exit(EXIT_SUCCESS);
// 	}
// }

// tokenize tout
// <infile token 1 token2 >outfile ... | token 1 token 2 token 3 |

// job 1 
// token 1 = ls token2 = -l
// 1 = commande 2 = arg
#define $LS ls

minishell struct 
{
	job* toutlesjobs;
}

token struct
{
	
}

job struct 
{
	int *pipe_exit = pipedes[0];
}