/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 19:44:20 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/05 18:21:39 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ms_execute_redir(t_job *j, t_exec *ex, int i)
{
	j->fd_infile = dup(STDIN_FILENO);
	j->fd_outfile = dup(STDOUT_FILENO);
	if (i > 0)
	{
		dup2(ex->pipes[i - 1][0], STDIN_FILENO);
	}
	if (i < (ex->n_jobs - 1))
	{
		dup2(ex->pipes[i][1], STDOUT_FILENO);
	}
	if (j->redir)
	{
		if (ms_execute_fileredir(j))
		{
			return (1);
		}
	}
	return (0);
}

void	heredoc_helper(char *str)
{
	printf("☠️  MinisHell: warning: here-document delimited");
	printf(" by end of file (wanted '%s')\n", str);
}

void	redir_heredoc(t_redir *r, int *fd)
{
	char	*nline;

	*fd = open(".tmp", O_RDWR | O_CREAT | O_TRUNC, 0755);
	if (*fd < 0)
		exit(1);
	close(*fd);
	while (1)
	{
		*fd = open(".tmp", O_APPEND | O_RDWR);
		nline = readline("> ");
		if (!nline)
		{
			heredoc_helper(r->target);
			break ;
		}
		if (ms_strcmp(r->target, nline))
			break ;
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
