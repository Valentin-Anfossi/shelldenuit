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

typedef struct s_token t_token;

typedef struct s_token
{
    char		*content;
    int        type;
    t_token    *next;
} t_token;


t_token	*token_last(t_token *lst);
void	token_add_back(t_token **lst, t_token *token);
int	ms_strcmp(char *str1, char *str2);
int	ms_lstsize(t_token *lst);
t_token *malloc_token(void);
void debug_print_tokens(t_token **tokens);