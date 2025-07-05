/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_fileredirs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 20:10:53 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/05 02:54:21 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ms_fileredir_outfd(t_redir *r, int *out_fd)
{
	if (r->type == R_OUT)
	{
		if(*out_fd != -1)
			close(*out_fd);
		*out_fd = open(r->target, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0777);
		if (*out_fd < 0)
			return (1);
	}
	else if (r->type == R_APPEND) 
	{
		if(*out_fd != -1)
			close(*out_fd);
		*out_fd = open(r->target, O_WRONLY | O_APPEND | O_CREAT | O_CLOEXEC, 0777);
		if (*out_fd < 0)
			return (1);
	}
	return (0);
}

int ms_fileredir_infd(t_redir *r, int *in_fd)
{
	if (r->type == R_IN) 
	{
		*in_fd = open(r->target, O_RDONLY | O_CLOEXEC);
		if(*in_fd < 0)
			return (1);
    } 
	else if (r->type == R_HEREDOC) 
	{
		*in_fd = ms_redir_heredoc(r, in_fd);
		if(*in_fd < 0)
			return (1);
	}
	return (0);
}

int ms_execute_fileredir(t_job *j) 
{
    t_redir *r;
    int out_fd = -1;
    int in_fd = -1;
    int error = 0;

    r = j->redir;
    while (r) 
	{
		if(ms_fileredir_outfd(r, &out_fd))
		{
			error = 1;
			break;
		}
		if(ms_fileredir_infd(r, &in_fd))
		{
			error = 1;
			break;
		}
        r = r->next;
    }
    if (error)
	{
        return (ms_redir_error(r->target, &out_fd, &in_fd));
	}
	return (ms_redir_apply(&out_fd, &in_fd));
}


int	ms_redir_apply(int *out_fd, int *in_fd)
{
    if (*out_fd != -1) 
	{
        if (dup2(*out_fd, STDOUT_FILENO) == -1) 
		{
            close(*out_fd);
            if (*in_fd != -1) 
				close(*in_fd);
            return (-1);
        }
        close(*out_fd);
    }
    if (*in_fd != -1) 
	{
        if (dup2(*in_fd, STDIN_FILENO) == -1) 
		{
            if (*out_fd != -1) 
				close(*out_fd);
            close(*in_fd);
            return (-1);
        }
		unlink(".tmp");
        close(*in_fd);
    }
    return (0);	
}

int 	ms_redir_heredoc(t_redir *r, int *fd)
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
	return (*fd);
}
