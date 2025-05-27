/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:20:37 by vanfossi          #+#    #+#             */
/*   Updated: 2025/05/27 20:10:06 by vanfossi         ###   ########.fr       */
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
#include <dirent.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>

typedef struct s_token	t_token;
typedef struct s_job	t_job;
typedef struct s_redir	t_redir;

extern pid_t gl_pid;

#ifndef BUFFER_SIZE
	#define BUFFER_SIZE 128;
#endif

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

enum Types
{
	SPC,
	DBQ,
	SQ,
	OUT,
	IN,
	APP,
	HER,
	ARG
};

typedef struct s_shell
{
	char	*cwd;
	char	**env;
	int		tuyau[2];
	int		exit_code;
	pid_t	mainpid;
}	t_shell;

typedef struct s_redir
{
	int		type;
	char	*target;
	t_redir	*next;
}	t_redir;

typedef struct s_job
{
	int		n;
	char	*cmd;
	char	**args;
	int		fd_infile;
	int		fd_outfile;
	int		error;
	t_redir	*redir;
	t_job	*piped_job;
}	t_job;

typedef struct s_token
{
	char	*content;
	int		type;
	t_token	*next;
}	t_token;

//TOKENS
t_token	**create_lst_tokens(char *line);
t_token	*malloc_token(void);
void	create_token(char *line, int start, int end, t_token **tokens);
void	split_token(char *line, int start, int end, t_token **tokens);
int		check_redirection_pipe(char *line);
int		is_tok_redir(t_token *t);
int		is_tok_arg(t_token *t);
int		is_str_exec(char *t);
int		is_tok_cmd(t_token *t);
int		is_tok_pipe(t_token *t);
t_token	*token_last(t_token *lst);
void	token_add_back(t_token **lst, t_token *token);
void	check_tokens(t_token **tokens);
void	typing_tokens(t_token **tokens);

//EXPAND
char	*expand_token_env(char *s, t_shell *shell);
void	check_env(t_token **tokens, t_shell *shell);

//JOBS
t_job	**create_lst_job(t_token **tokens);
t_job	*create_job(t_token **tokens);
t_job	*malloc_job(int lestoks);
int		get_redir_type(t_token *t);
int		check_jobs(t_job *jobs);
void	free_jobs(t_job *jobs);
void execute_fork(t_shell *s, t_job *j, int *tuyau);

//UTILS
void	debug_print_job(t_job *jobs);
void	debug_print_tokens(t_token **tokens);
int		ms_strcmp(char *str1, const char *str2);
int		ms_lstsize(t_token *lst);
char	**ms_cmdlst(void);
char	**ms_split(char *string, int c);
char	*ms_getenv(char *key, t_shell *s);
void	free_shell(t_shell *s);
int 	ms_execvp(char *file, char **argv, t_shell *s);
int		is_str_cmd(char *t);
int 	startswith(char *s, char *start);
int		is_folder(char *path);
char	**ms_fix_args(t_job *job);
int 	combiendetoks(t_token **t);
char	*ms_pathup(char *path, int n);
int		check_redirs(t_job *jobs);
int		is_executable(char *path);

//COMMANDS
void	select_command(t_job *jobs, t_shell *s);

//COMMANDS: CD
void	command_cd(t_job *j, t_shell *s);

//COMMANDS: PWD
void	command_pwd(t_job *j, t_shell *s);

//COMMANDS: ECHO
void	command_echo(t_job *j, t_shell *s);

//COMMANDS: EXPORT
void	command_export(t_job *j, t_shell *s);
void	modif_export(t_shell *s, char *vars, char *newstr);
void	add_to_env(t_shell *s, char *add_env);
int		check_export(char **vars, t_shell *shell, char *str);

//COMMANDS: UNSET
void	command_unset(t_job *j, t_shell *s);
void	unset_env(t_shell *s, char *str);

//COMMANDS: ENV
void	command_env(t_shell *shell);

//COMMANDS : EXIT
void	command_exit(t_job *j, t_shell *s);

//COMMANDS : EXECUTE
void	command_execute(t_job *j, t_shell *s);
int		execute_jobs(t_job *jobs, t_shell *shell);
void	execute_prog(t_job *j, t_shell *s);

//ERRORS
int		err_exp_ident(char *str);
int		err_cmd_nfound(char *str);