/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_wip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:12:48 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/19 07:31:17 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ms_execute_jobs(t_job *job, t_shell *sh)
{
	t_exec *ex;
	int i;
	int pid;
	int status;

	i = 0;
	ex = ms_exec_create(job,sh);
	if(ex->n_jobs == 1 && is_builtin(job->cmd))
		return (ms_execute_single(job,sh,ex));
	while(i < ex->n_jobs)
	{
		pid = fork();
		if(pid == 0)
		{
			//printf("Child\n");
			handle_signals_child();
			g_exitcode = ms_execute_child(job, ex, i);
			//ms_exec_resetredir(job);
			exit(g_exitcode);
			
			
		}
		else
		{
			ex->child_pids[i] = pid;
		}
		i ++;
		job = job->piped_job;
	}
	ms_pips_closeall(ex->pipes,ex->n_jobs);
	i = 0;
	printf("entering wait... \n");
	while(i < ex->n_jobs)
	{
		printf("Waiting pid:%d",(int)ex->child_pids[i]);
		waitpid(ex->child_pids[i], &status, WUNTRACED);
		g_exitcode = status;
		i ++;
	}
	handle_signals();
	return (0);
}

void	ms_pips_closeall(int(*pipes)[2], int n)
{
	int i;

	i = 0;
	while(i < n)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i ++;
	}
	free(pipes);
}

int ms_execute_child(t_job *j, t_exec *ex, int i)
{
	ms_pips_close(ex->pipes,ex->n_jobs,i);
	if(ms_execute_redir(j,ex, i))
		return (1);
	if(is_builtin(j->cmd))
		return(select_command(j,ex->shell));
	else
	{
		printf("execvp\n");
		return(ms_execvp(j->cmd, j->args, ex->shell));
	}
}

void ms_pips_close(int(*pipes)[2], int n, int j)
{
	int i;

	i = 0;
	while(i < n)
	{
		if(i != j-1)
			close(pipes[i][0]);
		if(i != j)
			close(pipes[i][1]);
		i ++;
	}	
}

int ms_execute_redir(t_job *j, t_exec *ex, int i)
{
	t_redir *r;


	j->fd_infile = dup(STDIN_FILENO);
	j->fd_outfile = dup(STDOUT_FILENO);
	//ms_pips_close(ex->pipes,ex->n_jobs,i);
	if (i > 0)
	{
		dup2(ex->pipes[i - 1][0], STDIN_FILENO);
		close(ex->pipes[i - 1][0]);
	}
	if (i < (ex->n_jobs - 1))
	{
		dup2(ex->pipes[i][1], STDOUT_FILENO);
		close(ex->pipes[i][1]);
	}
	if(ms_execute_fileredir(j))
		return(g_exitcode);
	return (0);
}

int	ms_execute_fileredir(t_job *j)
{
	t_redir *r;
	int out_fd;
	int in_fd;
	
	r = j->redir;
	while(r)
	{
		if(r->type == R_OUT)
			out_fd = open(r->target, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		else if(r->type == R_APPEND)
			out_fd = open(r->target, O_WRONLY | O_APPEND | O_CREAT, 0777);
		else if (r->type == R_IN)
			in_fd = open(r->target, O_RDONLY);	
		else if (r->type == R_HEREDOC)
			in_fd = ms_redir_heredoc(r, in_fd);	
		if (out_fd < 0 || in_fd < 0)
			return (ms_redir_error(out_fd, in_fd));
		r = r->next;
	}
	if(out_fd != -1)
		dup2(out_fd, STDOUT_FILENO);
	if(in_fd != -1)
		dup2(in_fd, STDIN_FILENO);
	return (0);
}

int ms_redir_error(int out_fd, int in_fd)
{
		
}

void ms_redir_heredoc(t_redir *r, int *fd)
{
	char *nline;

	*fd = open(".tmp", O_RDWR | O_CREAT | O_TRUNC, 0755);
	if(*fd < 0)
		exit(1);
	close(*fd);
	while(1)
	{
		*fd = open(".tmp", O_APPEND | O_RDWR);
		nline = readline("> ");
		if(!nline)
		{
			printf("☠️  MinisHell: warning: here-document delimited by end of file (wanted '%s')\n",r->target);
			break;
		}
		if(ms_strcmp(r->target,nline))
			break;
		ft_putstr_fd(nline,*fd);
		ft_putstr_fd("\n",*fd);
	}
	close(*fd);
	*fd = open(".tmp", O_RDONLY);
	dup2(*fd, STDIN_FILENO);
	unlink(".tmp");
	close(*fd);
}

void	ms_exec_resetredir(t_job *j)
{
	dup2(j->fd_infile, STDIN_FILENO);
	close(j->fd_infile);
	dup2(j->fd_outfile, STDOUT_FILENO);
	close(j->fd_outfile);
}

t_exec *ms_exec_create(t_job *job, t_shell *shell)
{
	t_exec *ex;
	
	ex = (t_exec *)malloc(sizeof(t_exec));
	ex->n_jobs = ms_count_jobs(job);
	ex->pipes = ms_create_pipes(ex->n_jobs - 1);
	ex->child_pids = (pid_t *)malloc(ex->n_jobs * sizeof(pid_t));
	ex->job = job;
	ex->shell = shell;
	ex->child_pids = (pid_t *)malloc(sizeof(pid_t) * ex->n_jobs);
	return (ex);
}

int (*ms_create_pipes(int n))[2]
{
	int (*pipes)[2];
	int i;
	
	pipes = (int (*)[2])malloc(n * sizeof(int [2]));
	i = 0;
	if(!pipes)
		return (NULL);
	while(i < n)
	{
		pipe(pipes[i]);
		i ++;
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


