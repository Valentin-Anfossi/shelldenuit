/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:36:54 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/14 19:12:18 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



int	execute_single_builtin(t_job *j, t_shell *s)
{
	if(ms_set_redirs(j))
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
	
	(void)j;
	if (pipes && n)
	{
		i = 0;
		while (i < n)
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
			i ++;
		}
		free(pipes);
	}
}

/*
int	execute_jobs(t_job *j, t_shell *s)
{
	int		n_j;
	int		n_p;
	int		i;
	int		h;
	int		status;
	int		(*pipes)[2];
	pid_t	*child_pids;
	pid_t	pid;

	n_j = n_jobs(j);
	n_p = n_j - 1;
	if (n_j == 1 && is_str_cmd(j->cmd)) 
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
	handle_signals_ign();
	while (i < n_j)
	{
		pid = fork();
		if (pid < 0)
			break ;
		if (pid == 0)
		{
			g_exitcode = -1;
			handle_signals_child();
			ms_exe_closepip_child(pipes, n_p, i);
			if (i > 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
			if (i < (n_j - 1))
				dup2(pipes[i][1], STDOUT_FILENO);
			if(execute_set_redirs(j))
			{
				exit(g_exitcode);
			}
			if (is_str_cmd(j->cmd))
			{
				g_exitcode = select_command(j, s);
				exit(g_exitcode);
			}
			g_exitcode = ms_execvp(j->cmd, j->args, s);
			if (g_exitcode)
				g_exitcode = err_cmd_nfound(j->cmd);
			exit(g_exitcode);
		}
		else
		{
			child_pids[i] = pid;
			//execute_closepipes(pipes, n_p, i);
		}
		i ++;
		j = j->piped_job;
	}
	s->child_pids = child_pids;
	h = 0;
	execute_closepipes(pipes, n_p, i);
	while (h < i)
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
}*/
void ms_exe_closepip_child(int (*pipes)[2], int n, int j)
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
