/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:23:05 by vanfossi          #+#    #+#             */
/*   Updated: 2025/05/20 15:29:19 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_jobs(t_job *jobs, t_shell *shell)
{
	int **pipes;
	t_job *j;
	int i;
	
	j = jobs;
	i = 0;
	while(j)
	{
		i ++;
		j = j->piped_job;
	}
	pipes = (int **)malloc(sizeof(int) *(i * 2));
	shell->pipefd = pipes;

	execute_fork(jobs,shell);
}

// Seulement la derniere redir est prise en compte mais les autres crees quand meme un fichier vide
void execute_prog(t_job *j, t_shell *s)
{
	int fd;
	char *buffer;
	int	bytes;

	buffer = (char *)malloc(BUFFER_SIZE);
	while(j->redir)
	{
		if(j->redir->type == R_IN)
		{
			fd = open(j->redir->target, O_RDONLY);
			dup2(fd,STDIN_FILENO);
		}
		if(j->redir->type == R_OUT)
		{
			fd = open(j->redir->target, O_CREAT | O_TRUNC | O_WRONLY, 0755);
			dup2(fd,STDOUT_FILENO);
		}
		if(j->redir->type == R_APPEND)
		{
			fd = open(j->redir->target, O_APPEND | O_WRONLY);
			dup2(fd,STDOUT_FILENO);
		}
		if(j->redir->type == R_HEREDOC)
		{
			//la flemme !
		}
		j->redir = j->redir->next;
	}
	if(is_str_cmd(j->cmd))
		select_command(j,s);
	else
	{
		ms_execvp(j->cmd,ms_fix_args(j),s);	
	}
}

char **ms_fix_args(t_job *job)
{
	char **args;
	int i;
	int j;

	i = 0;
	j = 0;

	while(job->args[i])
		i ++;
	args = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	args[j] = ft_strdup(job->cmd);
	j ++;
	while(job->args[i])
	{
		if(!ms_strcmp(" ",job->args[i]))
		{
			args[j] = ft_strdup(job->args[i]);
			printf("%s\n",args[j]);
			j ++;
		}
		i ++;
	}
	printf("CMD:%s",job->cmd);
	args[j] = NULL;
	return (args);
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
			{
				waitpid(n_pid,statloc,WUNTRACED);
				printf("Statloc: %d\n",*statloc);
			}
		}
		j = j->piped_job; 
	}
}


/*cree $? des le debut a 0
Modifier a chaque fin de fork par le execve/execvp*/