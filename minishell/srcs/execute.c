/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:23:05 by vanfossi          #+#    #+#             */
/*   Updated: 2025/05/13 02:33:58 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_jobs(t_job *jobs, t_shell *shell)
{
	int **pipes;
	int i;
	
	i = 0;
	while(jobs->piped_job)
	{
		pipes[i] = (int*)malloc(sizeof(int) * 2);
	}
	shell->pipefd = pipes;

	execute_fork(jobs,shell);
}

void execute_prog(t_job *j, t_shell *s)
{
	int fd;
	char *buffer;
	int	bytes;

	buffer = (char *)malloc(BUFFER_SIZE);
	if(j->redir)
	{
		if(j->redir->type == R_IN)
		{
			fd = open(j->redir->target, O_RDONLY);
			while((bytes = read(fd, buffer, BUFFER_SIZE) > 0))
			{
				write(STDIN_FILENO, buffer, bytes);
			}
			close(fd);
		}
	} 
	dup2(fd,STDIN_FILENO);
	
	
	if(is_str_cmd(j->cmd))
		select_command(j,s);
	else
	{
		ms_execvp(j->cmd,j->args,s);	
	}
	//command_execute(j,s);
}

void execute_fork(t_job *j, t_shell *s)
{
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
			execute_prog(j,s);
			exit(EXIT_FAILURE);
		}
		else
		{
			if(!j->piped_job)
				waitpid(n_pid,statloc,WUNTRACED);
		}
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