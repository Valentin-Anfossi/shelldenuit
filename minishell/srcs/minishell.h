/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:20:37 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/05 18:20:27 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _XOPEN_SOURCE 700
#define _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L

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
#include <linux/limits.h>

typedef struct s_token	t_token;
typedef struct s_job	t_job;
typedef struct s_redir	t_redir;

extern int				g_exitcode;

enum e_error
{
	NO_ERROR,
	ERR_CMD,
	ERR_NEWLINE
};

enum e_redirs
{
	R_IN,
	R_OUT,
	R_APPEND,
	R_HEREDOC
};

enum e_types
{
	SPC,
	DBQ,
	SQ,
	OUT,
	IN,
	APP,
	HER,
	ARG,
	PIP,
	INV,
	HERS
};

typedef struct s_shell
{
	char	*cwd;
	char	**env;
	int		exit_code;
	int		original_stdin;
	int		original_stdout;
	pid_t	*child_pids;
	pid_t	mainpid;
}	t_shell;

typedef struct s_tokenlst
{
	int		in_doubles;
	int		in_singles;
	int		start;
	int		end;
	char	*line;
	t_token	**t;
}	t_tokenlst;

typedef struct s_exec
{
	int		n_jobs;
	int		(*pipes)[2];
	pid_t	*child_pids;
	int		pid;
	t_job	*job;
	t_shell	*shell;
}	t_exec;

typedef struct s_redir
{
	int		type;
	char	*target;
	t_redir	*next;
}	t_redir;

typedef struct s_job
{
	int		n;
	int		pid;
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

typedef struct s_execvp
{
	char	*path;
	char	**dirs;
	char	**argv;
	char	*tmp;
	char	*file;
	t_shell	*s;
	int		i;
}	t_execvp;

typedef int (*pipes_ptr)[2];

//MS HEADER

//// MS TOKENS

t_token		**ms_tokens(char *line, t_shell *s);
t_token		**ms_lst_tokens(char *line);
void		ms_lst_types(t_token **t);
void		ms_lst_doubles(t_tokenlst *tlst);
void		ms_lst_singles(t_tokenlst *tlst);
void		ms_lst_spaces(t_tokenlst *tlst);
t_tokenlst	*ms_create_tlst(char *line, t_token **t);
void		*ms_free_tlst(t_tokenlst *tlst);
void		ms_token_split(char *line, int start, int end, t_token **tokens);
void		ms_token_create(char *line, int start, int end, t_token **tokens);
void		ms_token_addback(t_token **lst, t_token *token);
int			ms_is_redirpipe(char *line);
void		ms_free_tokens(t_token **lst);
int			ms_quotes(char *s);
void		ms_token_trim(t_token *t);
void		ms_lst_concat(t_token **t);
int			ms_token_isarg(t_token *t);
void		ms_token_concat(t_token *t, t_token *n);
void		ms_token_env(t_token **ts, t_shell *s);
char		*ms_token_expand(t_token *t, t_shell *s);
char		*ms_env_append(char *str, char *out, int i);
char		*ms_env_get(char *str, char *out, int i, t_shell *s);
char		**ms_env_split(char *s);
int			ms_env_length(char *str);
void		ms_rmv_spaces(t_token **t);
int			ms_error_syntax(t_token *t);
int			ms_tokens_check(t_token **t);
int			ms_token_type(t_token *t);
int			ms_tokens_pipcheck(t_token *cur, t_token **t);
t_token		*create_job_helper(t_token *t, t_job *j);
char		*ms_env_get(char *str, char *out, int i, t_shell *s);
int			combiendetoks(t_token **t);

//// MS EXECUTE
t_exec		*ms_exec_create(t_job *job, t_shell *shell);
pipes_ptr	ms_create_pipes(int n);
int			ms_execute_single(t_job *j, t_shell *s, t_exec *ex);
void		ms_free_ex(t_exec *ex);
void		ms_waitjobs(t_exec *ex, int i);
int			ms_execute_child(t_job *j, t_exec *ex, int i);
void		free_dirs(char **dirs);

// REDIRS
int			ms_execute_redir(t_job *j, t_exec *ex, int i);
int			ms_execute_fileredir(t_job *j);
int			ms_redir_heredoc(t_redir *r, int *fd);
int			ms_redir_error(char *str, int *out_fd, int *in_fd);
int			ms_redir_apply(int *out_fd, int *in_fd);
void		ms_exec_resetredir(t_job *j);

// PIPES
void		ms_pips_closeall(int (*pipes)[2], int n);
void		ms_pips_close(int (*pipes)[2], int n, int j);

// JOBS
int			ms_count_jobs(t_job *job);
int			ms_execute_jobs(t_job *job, t_shell *sh);
t_redir		*new_redir_create(t_token *t);
t_token		*add_to_job_redir(t_token *t, t_job *j);
t_token		*add_to_job_cmd(t_token *t, t_job *j);
t_token		*add_to_job_arg(t_token *t, t_job *j);
void		add_next_tok(t_token *t, t_job *j);

//// MS COMMANDS

//EXPORT
int			ms_command_export(t_job *j, t_shell *s);
int			ms_export_valid(char *str, t_shell *s);
int			ms_export_add(t_shell *s, char *add_env);
void		ms_free_env(char **env);
int			ms_check_export(char *str);;
int			ms_export_error(char *str);
int			ms_print_exported_vars(t_shell *s);
void		ms_free_split(char **split);

//UNSET
void		ms_remove_env(t_shell *s, int index);
int			ms_unset_env(t_shell *s, char *str);
int			ms_command_unset(t_job *j, t_shell *s);
int			ms_is_valid_var_name(char *str);

//CD
int			is_cd_valid(t_job *j);
void		cd_error(char *path);
int			cd_previous(t_shell *s);
int			cd_home(t_job *j, t_shell *s);
int			command_cd(t_job *j, t_shell *s);

//ECHO
void		command_echo_skip(t_job *j, int *i, int *n);
int			command_echo(t_job *j);

//ENV
int			command_env(t_shell *shell);

//EXIT
void		command_exit_helper(char *str);
void		command_exit(t_shell *s, t_job *j);

//MS DEBUG
void		ms_debug_print_tokens(t_token **tokens);

//TOKENS
t_token		**create_lst_tokens(char *line);
void		create_token(char *line, int start, int end, t_token **tokens);
void		split_token(char *line, int start, int end, t_token **tokens);
int			check_redirection_pipe(char *line);
int			is_tok_redir(t_token *t);
int			is_tok_arg(t_token *t);
int			is_str_exec(char *t);
int			is_tok_cmd(t_token *t);
int			is_tok_pipe(t_token *t);
t_token		*token_last(t_token *lst);
void		token_add_back(t_token **lst, t_token *token);

//EXPAND
char		*expand_token_env(char *s, t_shell *shell);
void		check_env(t_token **tokens, t_shell *shell);

//JOBS
t_job		**create_lst_job(t_token **tokens);
t_job		*create_job(t_token **tokens);
t_job		*malloc_job(int toks);
int			get_redir_type(t_token *t);
void		free_jobs(t_job *jobs);
void		execute_fork(t_shell *s, t_job *j, int *tuyau);

//EXECUTE
void		exit_all(t_shell *s, t_job *j);
int			is_builtin(char *cmd);
int			n_jobs(t_job *j);
void		wait_all(t_shell *s, t_job *j);
char		*find_cmd(char *path, t_shell *s, t_job *j);

//SIGNALS
void		signal_sigquit(int sig);
void		signal_parent_sigaction(void);
void		signal_child_sigaction(void);
void		handle_signals(void);
void		handle_signals_child(void);
void		signal_sigquit_child(int sig);
void		handle_signals_ign(void);

//UTILS
void		debug_print_job(t_job *jobs);
int			ms_strcmp(char *str1, const char *str2);
int			ms_lstsize(t_token *lst);
char		**ms_cmdlst(void);
char		**ms_split(char *string, int c);
char		*ms_getenv(char *key, t_shell *s);
void		free_shell(t_shell *s);
int			ms_execvp(char *file, char **argv, t_shell *s);
int			is_str_cmd(char *t);
int			startswith(char *s, char *start);
int			is_folder(char *path);
char		**ms_fix_args(t_job *job);
int			combiendetoks(t_token **t);
char		*ms_pathup(char *path);
int			check_redirs(t_job *jobs);
int			is_executable(char *path);
int			ms_setenv(char *env, char *str, t_shell *s);
int			ms_charraylen(char **ar);
void		free_tokens(t_token **t);
t_shell		*create_shell(void);

//COMMANDS
int			select_command(t_job *jobs, t_shell *s);

//COMMANDS: PWD
int			command_pwd(void);

//COMMANDS: EXPORT
int			command_export(t_job *j, t_shell *s);
void		modif_export(t_shell *s, char *vars, char *newstr);
void		add_to_env(t_shell *s, char *add_env);
int			check_export(char **vars, t_shell *shell, char *str);

//COMMANDS: UNSET
int			command_unset(t_job *j, t_shell *s);
int			unset_env(t_shell *s, char *str);

//COMMANDS: ENV
int			command_env(t_shell *shell);

//COMMANDS : EXIT
void		command_exit(t_shell *s, t_job *j);

//COMMANDS : EXECUTE
void		command_execute(t_job *j, t_shell *s);
int			execute_jobs(t_job *jobs, t_shell *shell);
void		execute_prog(t_job *j, t_shell *s);

//COMMANDS : STATUS
int			command_status(void);

//ERRORS
int			err_exp_ident(char *str);
int			err_cmd_nfound(char *str);
int			is_permited(char *path);
int			is_file(char *path);
