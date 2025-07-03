/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_wip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:12:48 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/03 03:20:03 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ms_execute_jobs(t_job *job, t_shell *sh)
{
    t_exec *ex;
    int i;
    int status;
    int exit_code = 0;

	ex = ms_exec_create(job, sh);
    if (ex->n_jobs == 1 && is_builtin(job->cmd)) 
		return (ms_execute_single(job, sh, ex));
	else {
        i = 0;
        while (i < ex->n_jobs) {
            ex->child_pids[i] = fork();
            if (ex->child_pids[i] == 0) {
                handle_signals_child();
                exit(ms_execute_child(job, ex, i));
            }
            job = job->piped_job;
            i++;
        }
		ms_pips_closeall(ex->pipes, ex->n_jobs - 1);
		int h;
		h = 0;
		while (h < i)
		{
			waitpid(ex->child_pids[h], &status, WUNTRACED);
			if(WIFSIGNALED(status))
			{
				if((128 + WTERMSIG(status)) == 131 && h == (i-1))
					ft_putstr_fd("Quit (core dumped)\n",STDERR_FILENO);
				if((128 + WTERMSIG(status)) == 130 && h == (i-1))
					ft_putstr_fd("\n",STDERR_FILENO);
				g_exitcode = 128 + WTERMSIG(status);
			}
			else if(status >= 256)
				g_exitcode = status / 256;
			else
				g_exitcode = status;
			h ++;
		}
    }
	ms_free_ex(ex);
    handle_signals();

    return (0);
}

void ms_free_ex(t_exec *ex)
{
	free(ex->pipes);
	free(ex->child_pids);
	free(ex);
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
	//free(pipes);
}

int ms_execute_child(t_job *j, t_exec *ex, int i)
{
	int code;

	code = 0;
	if(ms_execute_redir(j,ex, i))
		return (1);
	ms_pips_close(ex->pipes,ex->n_jobs - 1,i);
	if(is_builtin(j->cmd))
		return(select_command(j,ex->shell));
	else
	{
		code = ms_execvp(j->cmd, j->args, ex->shell);
		if(code)
			code = err_cmd_nfound(j->cmd);
		return(code);
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
	j->fd_infile = dup(STDIN_FILENO);
	j->fd_outfile = dup(STDOUT_FILENO);
	if (i > 0)
	{
		dup2(ex->pipes[i - 1][0], STDIN_FILENO);
		//close(ex->pipes[i - 1][0]);
	}
	if (i < (ex->n_jobs - 1))
	{
		dup2(ex->pipes[i][1], STDOUT_FILENO);
		//close(ex->pipes[i][1]);
	}
	if(j->redir)
	{
		if(ms_execute_fileredir(j))
		{
			return(1);
		}
	}
	return (0);
}

int ms_execute_fileredir(t_job *j) {
    t_redir *r;
    int out_fd = -1; // Initialiser à -1 pour indiquer aucun fichier ouvert
    int in_fd = -1;  // Initialiser à -1 pour indiquer aucun fichier ouvert
    int error = 0;

    r = j->redir;
    while (r) {
        if (r->type == R_OUT) {
			if(out_fd != -1)
				close(out_fd);
            out_fd = open(r->target, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0777);
            if (out_fd < 0) {
                error = 1;
                break;
            }
        } else if (r->type == R_APPEND) {
			if(out_fd != -1)
				close(out_fd);
            out_fd = open(r->target, O_WRONLY | O_APPEND | O_CREAT | O_CLOEXEC, 0777);
            if (out_fd < 0) {
                error = 1;
                break;
            }
        } else if (r->type == R_IN) {
            in_fd = open(r->target, O_RDONLY | O_CLOEXEC);
            if (in_fd < 0) {
                error = 1;
                break;
            }
        } else if (r->type == R_HEREDOC) {
            in_fd = ms_redir_heredoc(r, &in_fd);
            if (in_fd < 0) {
                error = 1;
                break;
            }
        }
        r = r->next;
    }

    if (error) {
        // Fermer les descripteurs ouverts avant de retourner une erreur
        if (out_fd != -1) {
            close(out_fd);
        }
        if (in_fd != -1) {
            close(in_fd);
        }
        return (ms_redir_error(r->target));
    }

    // Appliquer les redirections
    if (out_fd != -1) {
        if (dup2(out_fd, STDOUT_FILENO) == -1) {
            perror("dup2");
            close(out_fd);
            if (in_fd != -1) close(in_fd);
            return (-1);
        }
        close(out_fd); // Fermer le descripteur original après dup2
    }
    if (in_fd != -1) {
        if (dup2(in_fd, STDIN_FILENO) == -1) {
            perror("dup2");
            if (out_fd != -1) close(out_fd);
            close(in_fd);
            return (-1);
        }
        close(in_fd); // Fermer le descripteur original après dup2
    }

    return (0);
}


int ms_redir_error(char *str)
{
	if(ft_strlen(str) == 0)
		return (0);
	if (is_file(str) && !is_permited(str))
	{
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
		g_exitcode = 126;
	}
	if (is_file(str) == 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		g_exitcode = 1;
	}
	return (g_exitcode);
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
	return (ex);
}

int (*ms_create_pipes(int n))[2]
{
	int (*pipes)[2];
	int i;
	
	if(n == 0)
		return (NULL);
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


