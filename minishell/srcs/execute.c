/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:23:05 by vanfossi          #+#    #+#             */
/*   Updated: 2025/05/11 02:37:58 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_jobs(t_job *jobs, t_shell *shell)
{
	// ici on a tout les jobs
	//faut creer les pipes avant de fork

	int **pipes;
	int i;
	
	i = 0;
	while(jobs->piped_job)
	{
		pipes[i] = (int*)malloc(sizeof(int) * 2);
	}
	shell->pipefd = pipes;

	//ensuite on peut fork ?
	execute_fork(jobs,shell);
}

void execute_prog(t_job *j, t_shell *s)
{
	// du coup cette fonction c'est le job qui s'execute
	// faut s'occuper des redirections d'abord
	// par ex si y'a un infile il faut faire
	int fd;
	// faut ouvrir le fichier
	if(j->redir)
	{
		if(j->redir->type == R_IN)
			fd = open(j->redir->target, O_RDONLY);// j'ai pas les liste auto, je vais voir le .h
	}
	dup2(fd,STDIN_FILENO);
	//faudrait faire une fonction qui lit le fichier et le "feed" dans STDIN
	//on a le droit a read()

	
	
	//comment on lit un fichier lol c'est un nom en argument non ?
	select_command(j,s);
	command_execute(j,s);
}

void execute_fork(t_job *j, t_shell *s)
{
	ft_printf("ENTER PROG\n");
	int *statloc;
	
	statloc = (int *)malloc(sizeof(int));
	while (j)
	{
		pid_t n_pid = fork();
		if (n_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (n_pid == 0)
		{
			dup2(pipefd[0],STDOUT_FILENO);
			execute_prog(j,s); // ok je comprend petit a peti
			exit(EXIT_FAILURE); // 
		}
		else //Faut seulement wait le dernier job
		{
			if(!j->piped_job) // tu as raison je pense 
				waitpid(n_pid,statloc,WUNTRACED); //bah on rentre que si job n'a pas de piped job donc c'est le dernier non ?
		} // je sais meme pas comment pipe
		j = j->piped_job; 
	}
}

void command_execute(t_job *j, t_shell *s)
{
	ft_printf("ENTER EXECUTE\n");
	if(startswith(j->cmd,"./"))
		execute_fork(j,s);
	else
		err_cmd_nfound(j->cmd);
}