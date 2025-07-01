/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:26:38 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/12 19:26:42 by vanfossi         ###   ########.fr       */
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

int	ms_set_redirs(t_job *j)
{
	int in_fd;
	int out_fd;
	t_redir	*r;


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
		in_fd = 0;
		out_fd = 0;
		open_file(j, j->redir, in_fd, out_fd);
		if(r->type == R_HEREDOC)
			redir_heredoc(r,&in_fd);
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
}

int open_file(t_job *j, t_redir *r, int in_fd, int out_fd)
{
	j->fd_outfile = dup(STDOUT_FILENO);
	j->fd_infile = dup(STDIN_FILENO);
	if (j->fd_outfile < 0 || j->fd_infile < 0)
	{
		perror("dup");
		exit(1);
	}
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
	return (0);
}

	

/*int check_redirs(t_job *jobs)
{
	t_job *j;
	t_redir *r;

	j = jobs;
	while (j)
	{
		r = j->redir;
		while(r)
		{
			open_file(j, r);
			r = r->next;			
		}
		j = j->piped_job;
	}
	return (0);
}*/