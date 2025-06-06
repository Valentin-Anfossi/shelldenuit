#include "minishell.h"

int open_heredoc(char *target) // A FAIRE
{
	// int	fd_hdoc;
	// char *buf;

	// buf = readline(">");
	// fd_hdoc = open("tmp_heredoc.txt", O_CREAT | O_RDWR, 0777);
	// while (buf != target)
	// {
	// 	ft_strjoin(buf, "\n");
	// 	ft_putstr_fd(buf, fd_hdoc);
	// }
	// dup2(fd_hdoc, STDIN_FILENO);.
	(void)target;
	return (0);
}

int open_file(t_job *j, t_redir *r)
{
	if(r->type == R_IN)
	{
        if (j->fd_infile > -2)
		    close(j->fd_infile);
		j->fd_infile = open(r->target, O_RDONLY);
	}
	if(r->type == R_HEREDOC)
	{
        if (j->fd_infile > -2)
		    close(j->fd_infile);	
		j->fd_infile = open_heredoc(r->target);
	}
	if(r->type == R_OUT)
	{
        if (j->fd_outfile > -2)
		    close(j->fd_outfile);	
		j->fd_outfile = open(r->target, O_TRUNC | O_CREAT | O_WRONLY, 0744);
	}
	if(r->type == R_APPEND)
	{
        if (j->fd_infile > -2)
		    close(j->fd_outfile);
		j->fd_outfile = open(r->target, O_APPEND | O_CREAT | O_WRONLY, 0744);
	}
	return (0);
}

int check_redirs(t_job *jobs)
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
}