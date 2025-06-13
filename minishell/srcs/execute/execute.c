/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:36:54 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/12 19:26:15 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void redir_heredoc(t_redir *r, int *fd)
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

int	execute_set_redirs(t_job *j)
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
				perror(r->target);
				g_exitcode = 1;
				return (1);
			}
			//dup2(out_fd, STDOUT_FILENO);
			//close(out_fd);
		}
		else if (r->type == R_APPEND)
		{
			out_fd = open(r->target, O_WRONLY | O_APPEND | O_CREAT, 0777);
			if (out_fd < 0)
			{
				perror(r->target);
				g_exitcode = 1;
				return (1);
			}
			//dup2(out_fd, STDOUT_FILENO);
			//close(out_fd);
		}
		else if (r->type == R_IN)
		{
			in_fd = open(r->target, O_RDONLY);
			if (in_fd < 0)
			{
				perror(r->target);
				g_exitcode = 1;
				return (1);
			}
			//dup2(in_fd, STDIN_FILENO);
			//close(in_fd);
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
	return (0);
}

void	execute_reset_redirs(t_job *j)
{
	if (dup2(j->fd_outfile, STDOUT_FILENO) < 0)
	{
		perror("stdout restore");
		exit(1);
	}
	close(j->fd_outfile);
	if (dup2(j->fd_infile, STDIN_FILENO) < 0)
	{
		perror("stdin restore");
		exit(1);
	}
	close(j->fd_infile);
}

int	execute_single_builtin(t_job *j, t_shell *s)
{
	if(execute_set_redirs(j))
		return (g_exitcode);
	//ms_fix_args(j);
	g_exitcode = select_command(j, s);
	execute_reset_redirs(j);
	return (1);
}

//Close pipes, where n is number of pipes
void execute_closepipes(int (*pipes)[2], int n, int j)
{
	int i;
	
	if (pipes && n)
	{
		i = 0;
		while (i < n)
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			i ++;
		}
	}
}


int	execute_jobs(t_job *j, t_shell *s)
{
	int		n_j;
	int		n_p;
	int		i;
	int		h;
	int		status;
	int		exit_status;
	int		(*pipes)[2];
	pid_t	*child_pids;
	pid_t	pid;

	n_j = n_jobs(j);
	n_p = n_j - 1;
	if (n_j == 1 && is_str_cmd(j->cmd)) // IF ONE JOB && BUILTIN WE DONT FORK (WHY ? WE SHOULD FORK IF ITS NOT A BUILTIN BECAUSE EXECVE REPLACES THE CURRENT PROCESS, SO IT CLOSES THE SHELL WHEN ITS DONE (AND WE DONT WANT THAT), BUT IF WE FORK IT WE CANT MODIFY THE ENV VARIABLES (AND BASH DOESNT DO IT EITHER), SO, SINCE WE HAVE TO BUILTIN THE TWO COMMANDS THAT CAN MODIFIY THE ENV VARIABLES, WE CAN SIMPLY NOT FORK AND EXECUTE EVERYTHING IN THE PARENT PROCESS AND IT WORKS ca va la forme ? pti ☕ ?)
		return (execute_single_builtin(j, s));
	pipes = (int (*)[2])malloc((n_p) * sizeof(int [2]));
	if (!pipes)
		return (-1);
	i = 0;
	h = 0;
	while (i < n_p)
	{
		if (pipe(pipes[i]) == -1)
		{
			//NEEDS TO CLOSE PIPES AND FREE IF IT FAILS
			return (-1); //ERROR PIPE
		}
		i++;
	}
	child_pids = (pid_t *)malloc(n_j * sizeof(pid_t));
	if (!child_pids)
	{
		//NEEDS TO CLOSE PIPES AND FREE IF IT FAILS
		return (-1); //ERROR MALLOC
	}
	i = 0;
	//IGNORE SIGNALS WHILE EXECUTE
	handle_signals_ign();
	while (i < n_j) // MAIN LOOP FOR FORKS
	{
		pid = fork();
		if (pid < 0)
			break ;
		if (pid == 0) //CHILD
		{
			g_exitcode = -1;
			handle_signals_child();
			if (i > 0) //SI PAS 1ERE CMD ON CONNECT LA STDIN AU PIPE PRECEDENT
				dup2(pipes[i - 1][0], STDIN_FILENO);
			if (i < (n_j - 1)) //SI PAS DERNIERE CMD ON CONNECT LE STDOUT AU PIPE
				dup2(pipes[i][1], STDOUT_FILENO);
			if(execute_set_redirs(j))
			{
				execute_closepipes(pipes,n_p,i);
				exit(g_exitcode);
			}
			execute_closepipes(pipes,n_p,i);
			//ON EXECUTE
			if (is_str_cmd(j->cmd))
			{
				g_exitcode = select_command(j, s);
				exit(g_exitcode);
			}
			g_exitcode = ms_execvp(j->cmd, j->args, s);
			if (g_exitcode)
				g_exitcode = err_cmd_nfound(j->cmd, s);
			exit(g_exitcode);
		}
		else //PARENT
		{
			child_pids[i] = pid; // ON SAVE LE PID DU CHILD
			//kill(child_pids[i],SIGQUIT);
			if(i > 0)
			{
				close(pipes[i-1][1]);
				close(pipes[i-1][0]);
			}
		}
		i ++;
		j = j->piped_job;
	}
	s->child_pids = child_pids;
	//PARENT
	//ON CLOSE LES PIPES
	h = 0;

	/*
	signal(SIGQUIT, SIG_IGN);
	printf("Processus parent (PID: %d) envoie un signal SIGQUIT au processus enfant (PID: %d)\n", getpid(), pid);
    sleep(1); // Attendre un peu pour s'assurer que le processus enfant est prêt
    kill(pid, SIGQUIT); // Envoyer le signal SIGQUIT au processus enfant
    wait(NULL); // Attendre que le processus enfant se termine
	*/
	
	execute_closepipes(pipes, n_p, i);
	while (h < i) //ON WAIT TOUT LES CHILDS
	{
		waitpid(child_pids[h], &status, WUNTRACED);
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
	handle_signals();
	free(child_pids);
	return (0);
}
