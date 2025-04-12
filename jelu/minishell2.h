#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h> 
#include <stdlib.h>
#include "../vanf/libft/libft.h"
#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define CMD 1;
#define ARG 2;
#define REDIR_IN 3;
#define REDIR_OUT 4;
#define HEREDOC 5;
#define PIPE 6;


typedef struct t_token
{
	char 	*now;
	int		type;       
	t_token	*next;
	t_token	*prev;
} s_token;