/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:20:37 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/14 18:00:48 by vanfossi         ###   ########.fr       */
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

#define CMD 1;
#define ARG 2;
#define REDIR_IN 3;
#define REDIR_OUT 4;
#define HEREDOC 5;
#define APPEND 6;
#define PIPE 7;
#define SPC 8;
#define ENV 9;
#define ECHO 10;
#define CD 11;
#define PWD 12;
#define EXPORT 13;
#define UNSET 14;
#define EXIT 15;

 
typedef struct t_token s_token;

typedef struct t_shell
{
	char *path;
	char *line;
	char **envs_id;
	char **envs;
} s_shell;

typedef struct t_job
{
	int id;
	int command;
	char *exec_path;
	char *infile_path;
	char *outfile_path;
	char *args;
	int pipefd[2];
	s_token *tokens;
} s_job;

typedef struct t_token
{
    char		*content;
    int        type;
    s_token    *next;
} s_token;

s_token **tokenizer_start(char *line);
int tokenizer(char *line, s_token **tokens, int i);
int tokenizer_helper(char *line, int i, s_token **tokens);
int check_tokens_list(s_token **tokens);
char *create_input_line(char *line);
int replace_env(char *line, int i, s_token **tokens);
int token_exec(char *line, int i, s_token **tokens);
int token_append(char *line, int i, s_token **tokens);
int token_heredoc(char *line, int i, s_token **tokens);
int token_outfile(char *line, int i, s_token **tokens);
int token_infile(char *line, int i, s_token **tokens);
int token_pipe(char *line, int i, s_token **tokens);
int token_char(char *line, int i, s_token **tokens);
void token_space(s_token **tokens);
void	token_add_back(s_token **lst, s_token *new);
s_token	*token_last(s_token *lst);
int check_for_commands(char *line, int i);
void delete_tokens(s_token **tokens);
void create_jobs(s_token **tokens);
char *get_error(int type);

int	ms_strcmp(char *str1, char *str2);
int	ms_lstsize(s_token *lst);


void debug_print_tokens(s_token **tokens);
