/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:33:10 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/25 09:35:47 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Execve a besoin du path COMPLET (/home/vanfossi/blablabla)
//l'arg Env de execve determine si il recoit les variable d'enviro
//env = null par ex, il a acces a rien
//pour l'env actuel de l'os c'est extern char **environ;
//mais jpense faut faire le notre avec nos variables non ? (c pas precise mais ca ferait sens)

void test_redir(t_job *job)
{
	int fd; 
	char ** argv;
	char *env;
	
	fd = open("output",O_WRONLY | O_CREAT);
	argv = NULL;
	env = NULL;
	dup2(fd, STDOUT_FILENO);
	close(fd);
	ft_printf("hello ?\n");
	execve("/bin/ls",argv,env);
	exit(EXIT_FAILURE);
}

//They took er jebs!
// Est ce quil faut rien faire avec le parent thread ?
// Je sais pas trop
// Aussi les redirections out (out et out_append) on peut les faire sans pipe
// dup2 ca fonctionne tres bien (woopi)
void execute_jobs(t_job *jobs)
{
	while(jobs)
	{
		pid_t n_pid = fork();
		if(n_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		// CHILD FORK
		if(n_pid == 0)
		{
			test_redir(jobs);
			exit(EXIT_SUCCESS);
		}
		// PARENT FORK (DO NOTHING)
		else
		{
			waitpid(n_pid,NULL,WNOHANG);
		}
		jobs = jobs->piped_job;
	}
}

int main(void)
{
	char *line;
	t_shell *shell;
	t_token **tokens;
	t_job	*jobs;

	while(1)
	{
		line = readline("labonneshell :");
		if(line)
			tokens = create_lst_tokens(line);
		//type_tokens(tokens);
		//debug_print_tokens(tokens);
		jobs = create_job(tokens);
		if(!check_jobs(jobs))
			execute_jobs(jobs);
		debug_print_job(jobs);
		free_jobs(jobs);
	}
}



