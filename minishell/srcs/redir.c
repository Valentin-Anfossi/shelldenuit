#include "minishell.h"

// void *redirout(t_redir *redir, )
// {
//     t_redir *r;
//     int stdo;
//     int fd;

//     r = redir;
//     stdo = dup(STDOUT_FILENO);
//     fd = open(r->target, O_WRONLY | O_CREAT, 755);
//     dup2(fd, STDOUT_FILENO);
//     close(fd);
//     ft_printf("%s", return_echo);
// }

int open_heredoc(char *target)
{}

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
			open_file(j,r);
			r = r->next;			
		}
		j = j->piped_job;
	}
}