/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:20:37 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/18 03:12:11 by vanfossi         ###   ########.fr       */
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
#include "./libft/libft.h"
#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define ARG 1
#define RE_OUT 2
#define RE_APP 3
#define RE_IN 4
#define HEREDOC 5
#define QUO_S 6
#define QUO_D 7
#define SPC 8

typedef struct s_token  t_token;
typedef struct s_job    t_job;
typedef struct s_redir  t_redir;

typedef struct s_redir
{
    int     type;
    char    *target;
    t_redir *redir;
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


t_token	*token_last(t_token *lst);
void	token_add_back(t_token **lst, t_token *token);
int	ms_strcmp(char *str1, char *str2);
int	ms_lstsize(t_token *lst);
t_token *malloc_token(void);
void debug_print_tokens(t_token **tokens);
void debug_print_job(t_job **jobs);