/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 09:20:37 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/13 14:18:11 by vanfossi         ###   ########.fr       */
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

#define EXEC 1
 

typedef struct t_token s_token;

typedef struct t_shell
{
	char *path;
	char *line;
	char **envs_id;
	char **envs;
} s_shell;

typedef struct t_input
{
	int type;
	char *path;
	
} s_input;

typedef struct t_job
{
	int id;
	int command;
	char *exec_path;
	char *infile_path;
	char *outfile_path;
	char *args;
} s_job;

struct t_token
{
	int type;
	char *content;
	s_token *next;
};

//Token types
// 1 = exec, 2 = infile, 3 = outfile, 4 = heredoc
// 5 = outfileappend, 6 = pipe, 7 env variables, 8 = args