/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:20:37 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/14 21:24:44 by vanfossi         ###   ########.fr       */
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

#define CMD 1
#define ARG 2
#define REDIR_IN 3
#define REDIR_OUT 4
#define HEREDOC 5
#define APPEND 6
#define PIPE 7
#define SPC 8
#define ENV 9
#define ECHO 10
#define CD 11
#define PWD 12
#define EXPORT 13
#define UNSET 14
#define EXIT 15
#define ARGSIN 20
#define ARGDOU 21

typedef struct s_token	t_token;

typedef struct s_token
{
	char	*content;
	int		type;
	t_token	*next;
}	t_token;

typedef struct s_shell
{
	char	*path;
	char	*line;
	char	**envs_id;
	char	**envs;
}	t_shell;

typedef struct s_job
{
	int		id;
	int		command;
	char	*exec_path;
	char	*infile_path;
	char	*outfile_path;
	char	*args;
	int		pipefd[2];
	t_token	*tokens;
}	t_job;

t_token	**tokenizer_start(char *line);
int		tokenizer(char *line, t_token **tokens, int i);
int		tokenizer_helper(char *line, int i, t_token **tokens);

int		token_exec(char *line, int i, t_token **tokens);
int		token_pipe(char *line, int i, t_token **tokens);
int		token_char(char *line, int i, t_token **tokens);
void	token_space(t_token **tokens);

int		token_quotes(char *line, int i, t_token **tokens);
int		token_append(char *line, int i, t_token **tokens);
int		token_heredoc(char *line, int i, t_token **tokens);
int		token_outfile(char *line, int i, t_token **tokens);
int		token_infile(char *line, int i, t_token **tokens);

t_token	**create_tokenlst(void);
t_token	*create_token(void);
t_token	*token_last(t_token *lst);
void	token_add_back(t_token **lst, t_token *token);
void	delete_tokens(t_token **tokens);

int		check_tokens_list(t_token **tokens);
int		check_for_commands(char *line, int i);
int		check_les_chevrons(char *line, int i);
char	*get_error(int type);

int		replace_env(char *line, int i, t_token **tokens);
char	*create_input_line(char *line);
int		ms_strcmp(char *str1, char *str2);
int		ms_lstsize(t_token *lst);

void	create_jobs(t_token **tokens);

void	debug_print_tokens(t_token **tokens);
