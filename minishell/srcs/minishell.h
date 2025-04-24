/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:20:37 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/24 10:36:36 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h> 
#include <stdlib.h>
#include "../libft/libft.h"
#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


typedef struct s_token  t_token;
typedef struct s_job    t_job;
typedef struct s_redir  t_redir;

enum Error
{
	NO_ERROR,
	ERR_CMD,
	ERR_NEWLINE
};

enum Redirs
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
};

typedef struct s_shell
{
	char *cwd;
} t_shell;

typedef struct s_redir
{
    int     type;
    char    *target;
    t_redir *next;
}   t_redir;

typedef struct s_job
{
    char    *cmd; // checker le premier token ARG, si c'est pas une commande message d'erreur (si il y a un pipe continuer vers le prochain job)
    char    **args; // les argument de la commande. exemple : -n "fait chier le parsing il faut une IA parseuse"
    int     error;
    t_redir *redir;  //redir[0] = le type de redirection et redir[1] l'endroit ou rediriger (ou le EOF du heredoc)
    t_job   *piped_job;  // en cas de pipe, go vers un nouveau job en partant du token suivant
}    t_job;

typedef struct s_token
{
    char		*content;
    int        type;
    t_token    *next;
}   t_token;

//TOKENS
t_token	**create_tokens(char *line);
void 	create_token(char *line, int start, int end, t_token **tokens);
void 	split_token(char *line, int start, int end, t_token **tokens);
void 	append_token(t_job *job, t_token *tok);
t_token	**create_lst_tokens(char *line);
t_token	*token_last(t_token *lst);
void	token_add_back(t_token **lst, t_token *token);
t_token *malloc_token(void);
int 	check_redirection_pipe(char *line);
int get_redir_type(t_token *t);

//JOBS
t_job	*create_lst_job(t_token **tokens);
t_job	*create_job(t_token **tokens);
t_job	*malloc_job(void);
int is_tok_redir(t_token *t);
int is_tok_arg(t_token *t);
int is_tok_cmd(t_token *t);
int is_tok_pipe(t_token *t);
t_token *add_to_job_redir(t_token *t, t_job *j);
t_token *add_to_job_cmd(t_token *t, t_job *j);
t_token *create_redir(t_token *t, t_job *j);
int check_jobs(t_job *jobs);
void free_jobs(t_job *jobs);


//UTILS
void 	debug_print_job(t_job *jobs);
void 	debug_print_tokens(t_token **tokens);
int		ms_strcmp(char *str1, char *str2);
int		ms_lstsize(t_token *lst);
char 	**ms_cmdlst();
