#include "minishell.h"

void *redirout(t_redir *redir, )
{
    t_redir *r;
    int stdo;
    int fd;

    r = redir;
    stdo = dup(STDOUT_FILENO);
    fd = open(r->target, O_WRONLY | O_CREAT, 755);
    dup2(fd, STDOUT_FILENO);
    close(fd);
    ft_printf("%s", return_echo);
}