/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_wip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:12:48 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/15 03:08:23 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*int	ms_set_redirs(t_job *j)
{
	t_redir	*r;
	int		out_fd;
	int		in_fd;

	j->fd_outfile = dup(STDOUT_FILENO);
	j->fd_infile = dup(STDIN_FILENO);
	if (j->fd_outfile < 0 || j->fd_infile < 0)
	{
		perror("dup");
		exit(1);
	}
	r = j->redir;
	while (r)
	{
		if (r->type == R_OUT)
		{
			out_fd = open(r->target, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (out_fd < 0)
			{
				dup2(j->fd_infile, STDIN_FILENO);
   				dup2(j->fd_outfile, STDOUT_FILENO);
    			close(j->fd_infile);
    			close(j->fd_outfile);
				perror(r->target);
				g_exitcode = 1;
				return (1);
			}
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		else if (r->type == R_APPEND)
		{
			out_fd = open(r->target, O_WRONLY | O_APPEND | O_CREAT, 0777);
			if (out_fd < 0)
			{
				dup2(j->fd_infile, STDIN_FILENO);
   				dup2(j->fd_outfile, STDOUT_FILENO);
    			close(j->fd_infile);
    			close(j->fd_outfile);
				perror(r->target);
				g_exitcode = 1;
				return (1);
			}
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		else if (r->type == R_IN)
		{
			in_fd = open(r->target, O_RDONLY);
			if (in_fd < 0)
			{
				dup2(j->fd_infile, STDIN_FILENO);
   				dup2(j->fd_outfile, STDOUT_FILENO);
    			close(j->fd_infile);
    			close(j->fd_outfile);
				perror(r->target);
				g_exitcode = 1;
				return (1);
			}
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		else if(r->type == R_HEREDOC)
		{
			redir_heredoc(r,&in_fd);
		}
		r = r->next;
	}
	 if(in_fd)
	 	dup2(in_fd,STDIN_FILENO);
	 if(out_fd)
	 	dup2(out_fd,STDOUT_FILENO);
	close(out_fd);
	 close(in_fd);
	 close(j->fd_infile);
	close(j->fd_outfile);
	return (0);
}*/

int	ms_execute_jobs(t_job *job, t_shell *sh)
{
	t_exec *ex;
	int i;

	i = 0;
	if (ms_set_redirs(job))
		return (printf("error redir"));
	ex = ms_exec_create(job,sh);
	if(ex->n_jobs == 1 && is_builtin(job->cmd))
		return (ms_execute_single(job,sh));
	while(i < ex->n_jobs)
	{
		ex->pid = fork();
		if(ex->pid == 0)
		{
			handle_signals_child();
			exit(ms_execute_child(job, ex, i));
		}
		job = job->piped_job;
		i ++;
	}
}

int ms_execute_child(t_job *j, t_exec *ex, int i)
{
	//ms_pips_close(ex->pipes,ex->n_jobs,i);
	ms_pips_set(ex->pipes, ex->n_jobs, i);
	if(ms_set_redirs(j))
		return (g_exitcode);
	if(is_builtin(j->cmd))
		return(select_command(j,ex->shell));
	else
		return(ms_execvp(j->cmd, j->args, ex->shell));
}

void ms_pips_set(int(*pipes)[2], int nb_j, int j)
{

	if (j == 0)
	{
		close(pipes[j][0]);
		dup2(pipes[j][1], STDOUT_FILENO);
	}	
	else if (j == nb_j - 1)
	{
		dup2(pipes[j - 1][0], STDIN_FILENO);
		close(pipes[j - 1][1]);
		
	}
	else
	{
   		dup2(pipes[j - 1][0], STDIN_FILENO);
    	dup2(pipes[j][1], STDOUT_FILENO); 
	}
}	

int ms_execute_redir(t_job *j, t_exec *ex, int i)
{

	//check_redirs(j);
}

t_exec *ms_exec_create(t_job *job, t_shell *shell)
{
	t_exec *ex;
	
	ex = (t_exec *)malloc(sizeof(t_exec));
	ex->n_jobs = ms_count_jobs(job);
	ex->pipes = ms_create_pipes(ex->n_jobs);
	ex->child_pids = (pid_t *)malloc(ex->n_jobs * sizeof(pid_t));
	ex->job = job;
	ex->shell = shell;
	return (ex);
}

int (*ms_create_pipes(int n))[2]
{
	int (*pipes)[2];
	int	i;
	
	pipes = (int (*)[2])malloc(n * sizeof(int [2]));
	if(!pipes)
		return (NULL);
	i = 0;
	while (i < n)
	{
		if (pipe(pipes[i]) == -1)
		{
			free(pipes);
			return(NULL);
		}	
		i++;
	}
	return (pipes);
}


int ms_count_jobs(t_job *job)
{
	int n;
	
	n = 0;
	if(!job)
		return (n);
	while(job)
	{
		n ++;
		job = job->piped_job;
	}
	return (n);
}
