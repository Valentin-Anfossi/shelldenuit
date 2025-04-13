/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:20:37 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/13 20:06:18 by vanfossi         ###   ########.fr       */
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
#define APPEND 6;
#define PIPE 7;
#define ECHO 10;
#define CD 11;
#define PWD 12;
#define EXPORT 13;
#define UNSET 14;
#define ENV 15;
#define EXIT 16;
 
typedef struct t_token s_token;

typedef struct t_shell
{
	char *path;
	char *line;
	char **envs_id;
	char **envs;
	char **shell_cmds;
} s_shell;

typedef struct t_job
{
	int id;
	int command;
	char *exec_path;
	char *infile_path;
	char *outfile_path;
	char *args;
	s_token *tokens;
} s_job;

typedef struct t_token
{
    char        *now;
    int        type;
    s_token    *next;
} s_token;

s_token **tokenizer_start(char *line);
int token_exec(char *line, int i, s_token **tokens);
int token_append(char *line, int i, s_token **tokens);
int token_heredoc(char *line, int i, s_token **tokens);
int token_outfile(char *line, int i, s_token **tokens);
int token_infile(char *line, int i, s_token **tokens);
int token_pipe(char *line, int i, s_token **tokens);
int token_char(char *line, int i, s_token **tokens);
void	token_add_back(s_token **lst, s_token *new);
s_token	*token_last(s_token *lst);
int check_for_commands(char *line, int i);

int	ms_strcmp(char *str1, char *str2);


void debug_print_tokens(s_token **tokens);
