/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:36:54 by vanfossi          #+#    #+#             */
/*   Updated: 2025/05/30 01:13:42 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_jobs(t_job *j, t_shell *s)
{
	int n_j;
	int n_p;
	int (*pipes)[2];
	pid_t *child_pids;

	n_j = n_jobs(j);
	n_p = n_j - 1;
	
	// WE CREATE ALL THE PIPES (n jobs -1) BEFORE
	pipes = (int (*)[2])malloc((n_p) * sizeof(int[2]));
	if (!pipes)
		return (-1); //ERROR MALLOC
	
	int i = 0;
	int h = 0;
	while(i < n_p)
	{
		if(pipe(pipes[i]) == -1)
		{
			//NEEDS TO CLOSE PIPES AND FREE IF IT FAILS
			return (-1); //ERROR PIPE
		}
		i ++;
	}

	child_pids = (pid_t *)malloc(n_j * sizeof(pid_t));
	if(!child_pids)
	{
		//NEEDS TO CLOSE PIPES AND FREE IF IT FAILS
		return(-1); //ERROR MALLOC
	}
	
	i = 0;
	while(i < n_j) // MAIN LOOP FOR FORKS
	{
		pid_t pid = fork();
		if(pid < 0)
			break; //ERROR FORK
		if(pid == 0) //CHILD
		{
			printf("child\n");
			if(i > 0) //SI PAS 1ERE CMD ON CONNECT LA STDIN AU PIPE PRECEDENT
			{
				dup2(pipes[i - 1][0], STDIN_FILENO);
				printf("0\n");
			}
			if(i < (n_j - 1)) //SI PAS DERNIERE CMD ON CONNECT LE STDOUT AU PIPE
			{
				dup2(pipes[i][1], STDOUT_FILENO);
				printf("1\n");
			}
			if(pipe) // ON FERME LES PIPES DANS LE CHILD
			{
				printf("pipe\n");
				h = 0;			
				while(h < n_p)
				{
					close(pipes[h][0]);
					close(pipes[h][1]);
					h ++;
				}
			}
			//ON EXECUTE
			ms_fix_args(j);
			ms_execvp(j->cmd,j->args,s);
			exit(EXIT_FAILURE);
		}
		else //PARENT
		{
			child_pids[i] = pid; // ON SAVE LE PID DU CHILD
		}
		i ++;
		j = j->piped_job;
	}
	
	//PARENT
	//ON CLOSE LES PIPES
	if(pipes)
	{
		h = 0;			
		while(h < n_p)
		{
			close(pipes[h][0]);
			close(pipes[h][1]);
			h ++;
		}
	}
	h = 0;
	















	
	int status;
	while(h < i) //ON WAIT TOUT LES CHILDS
	{
		waitpid(child_pids[h],&status,WUNTRACED);
		printf("EXIT %d : %d\n",h,status);
		h ++;
	}
	free(child_pids);
	return (0);
}
