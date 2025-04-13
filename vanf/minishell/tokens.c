/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:39:07 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/13 20:11:16 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

s_token **create_tokenlst(void)
{
	s_token **tokens;

	tokens = (s_token **)malloc(sizeof(s_token *));
	*tokens = NULL;
	return (tokens);
}

s_token *create_token(void)
{
	s_token *new_token;

	new_token = (s_token *)malloc(sizeof(s_token));
	new_token->next = NULL;
	new_token->now = NULL;
	new_token->next = NULL;
	return (new_token);
}

s_token **tokenizer_start(char *line)
{
	int i;
	s_token **tokens;
	
	tokens = create_tokenlst();
	i = 0;
	while(line[i])
	{
		if(line[i] == '.' && line[i+1] && line[i+1] == '/')
			i = token_exec(line,i,tokens);
		else if(line[i] == '>' && line[i+1] && line[i+1] == '>')
			i = token_append(line,i,tokens);
		else if(line[i] == '<' && line[i+1] && line[i+1] == '<')
			i = token_heredoc(line,i,tokens);
		else if(line[i] == '>')
			i = token_outfile(line,i,tokens);
		else if(line[i] == '<')
			i = token_infile(line,i,tokens);
		else if(line[i] == '|')
			i = token_pipe(line,i,tokens);
		else if(line[i] && line[i] != ' ')
			i = token_char(line,i,tokens);
		else
			i ++;
	}
	return (tokens);
}

//Create a Executable token containing path and adds it to the list
int token_exec(char *line, int i, s_token **tokens)
{
	s_token *new_token;
	int end;

	end = i;
	while(line[end] && line[end] != ' ')
		end ++;
	new_token = create_token();
	new_token->type = CMD;
	new_token->now = ft_substr(line,i,end-i);
	token_add_back(tokens, new_token);
	return (end);
}

//Create a append token containing desired file name
int token_append(char *line, int i, s_token **tokens)
{
	s_token *new_token;
	int end;

	i += 2;
	while(line[i] == ' ')
		i ++;
	end = i;
	while(line[end] && line[end] != ' ')
		end ++;
	new_token = create_token();
	new_token->type = APPEND;
	new_token->now = ft_substr(line,i,end-i);
	token_add_back(tokens, new_token);
	return (end);
}

//Create a heredoc token containing STOP word
int token_heredoc(char *line, int i, s_token **tokens)
{
	s_token *new_token;
	int end;

	i += 2;
	while(line[i] && line[i] == ' ')
		i ++;
	end = i;
	while(line[end] && line[end] != ' ')
		end ++;
	new_token = create_token();
	new_token->type = HEREDOC;
	new_token->now = ft_substr(line,i,end-i);
	token_add_back(tokens, new_token);
	return (end);
}

//Create a outfile token containing desired file name
int token_outfile(char *line, int i, s_token **tokens)
{
	s_token *new_token;
	int end;

	i ++;
	while(line[i] && line[i] == ' ')
		i ++;
	end = i;
	while(line[end] && line[end] != ' ')
		end ++;
	new_token = create_token();
	new_token->type = REDIR_OUT;
	new_token->now = ft_substr(line,i,end-i);
	token_add_back(tokens, new_token);
	return (end);
}

//Create a infile token containing relative file path
int token_infile(char *line, int i, s_token **tokens)
{
	s_token *new_token;
	int end;

	i ++;
	while(line[i] && line[i] == ' ')
		i ++;
	end = i;
	while(line[end] && line[end] != ' ')
		end ++;
	new_token = create_token();
	new_token->type = REDIR_IN;
	new_token->now = ft_substr(line,i,end-i);
	token_add_back(tokens, new_token);
	return (end);
}

//Create a pipe token
int token_pipe(char *line, int i, s_token **tokens)
{
	s_token *new_token;
	int end;

	i ++;
	new_token = create_token();
	new_token->type = PIPE;
	new_token->now = NULL;
	token_add_back(tokens, new_token);
	return (i);
}

//Checks if token is a Shell command then create a arg token if not
int token_char(char *line, int i, s_token **tokens)
{
	s_token *new_token;
	int re;
	int end;
	
	end = i;
	re = check_for_commands(line, i);
	new_token = create_token();
	while(line[end] && line[end] != ' ')
		end ++;
	if(re)
		new_token->type = re;
	else
	{
		new_token->type = ARG;
		new_token->now = ft_substr(line, i, end - i);
	}
	token_add_back(tokens, new_token);
	return (end);
}

//Checks for commands (nooooo)
int check_for_commands(char *line, int i)
{
	char *substr;
	int end;

	end = i;
	while(line[end] != ' ')
		end++;
	substr = ft_substr(line,i,end-i);
	if (ft_strncmp("echo",substr,end - i) == 4)
		return (10);
	else if(ms_strcmp("cd",substr))
		return (11);
	else if(ms_strcmp("pwd",substr))
		return (12);
	else if(ms_strcmp("export",substr))
		return (13);
	else if(ms_strcmp("unset",substr))
		return (14);
	else if(ms_strcmp("env",substr))
		return (15);
	else if(ms_strcmp("exit",substr))
		return (16);
	else
		return (0);
}
