/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:39:07 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/14 01:25:35 by vanfossi         ###   ########.fr       */
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
	new_token->type = 0;
	new_token->content = NULL;
	new_token->next = NULL;
	return (new_token);
}

s_token **tokenizer_start(char *line)
{
	s_token **tokens;
	int i;
	
	tokens = create_tokenlst();
	i = 0;
	// line = create_input_line(line);
	while(line[i])
	{
		i = tokenizer(line,tokens,i);
		if(i < 0)
			{
				delete_tokens(tokens);
				break;
			}
	}
	return (tokens);
}



int check_single_quotes(char *line, int i)
{
	while(line[i])
	{
	}
	return(i++);
}

int tokenizer(char *line, s_token **tokens, int i)
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
	else if(line[i] == '"' || line[i] == '\'')
		i = token_quotes(line,i,tokens);
	else
		i = tokenizer_helper(line, i, tokens);
	return (i);
}

int token_quotes(char *line, int i, s_token **tokens)
{
	if(line[i] == '"')
		i = token_dblq(line, i, tokens);
	else if(line[i] == '\'')
		i = token_q(line,i, tokens);
	return (i);
}

int token_dblq(char *line, int i, s_token **tokens)
{
	int end;

	end = i;
	i++;
	while(line[i])
	{
		if(line[i]=='"')
			
	}
}

// "" can be a "-n" for echo command ONLY if it's separated by a space
// ie : echo "-n" bou == bou(without newline)
// but : echo "-n"bou == -nbou
// and : echo bou"-n" == bou-n
// "" can be a command, ie: "cd" .. works
// "" can be a path for cd , ie "cd" "vanf" works
// "" cannot be a pipe or >> << < >
// ie : echo bou ">" out == bou > out
// '' is the same except it doesnt expands the env variables in echo

//ENV Variables can contain commands/args/anything
// In case the command is not echo, they should be expanded and tokenized

int tokenizer_helper(char *line, int i, s_token **tokens)
{
	if(line[i] == '$' && line[i+1] && line[i+1] != '?' && line[i+1] != ' ')
		i = token_env(line,i,tokens);
	else if(line[i] && line[i] != ' ')
		i = token_char(line,i,tokens);
	else
	{
		token_space(tokens);
		i ++;
	}
	return (i);
}

int token_env(char *line, int i, s_token **tokens)
{
	s_token *new_token;
	int end;

	end = i;
	while(line[end] && line[end] != ' ')
		end ++;
	new_token = create_token();
	new_token->type = ENV;
	if(end - i == 0)
		new_token->content = NULL;
	else
		new_token->content = ft_substr(line,i,end-i);
	token_add_back(tokens, new_token);
	return (end);
}

void token_space(s_token **tokens)
{
	s_token *new_token;
	new_token = create_token();
	new_token->type = SPC;
	token_add_back(tokens, new_token);
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
	if(end - i == 0)
		new_token->content = NULL;
	else
		new_token->content = ft_substr(line,i,end-i);
	token_add_back(tokens, new_token);
	return (end);
}

//Create a append token containing desired file name
int token_append(char *line, int i, s_token **tokens)
{
	s_token *new_token;
	int end;

	i += 2;
	while(line[i] && line[i] == ' ')
		i ++;
	end = i;
	while(line[end] && line[end] != ' ' && check_les_chevrons(line, end))
		end ++;
	new_token = create_token();
	new_token->type = APPEND;
	if(end - i == 0)
		new_token->content = NULL;
	else
		new_token->content = ft_substr(line,i,end-i);
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
	while(line[end] && line[end] != ' ' && check_les_chevrons(line, end))
		end ++;
	new_token = create_token();
	new_token->type = HEREDOC;
	if(end - i == 0)
		new_token->content = NULL;
	else
		new_token->content = ft_substr(line,i,end-i);
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
	while(line[end] && line[end] != ' ' && check_les_chevrons(line, end))
		end ++;
	new_token = create_token();
	new_token->type = REDIR_OUT;
	if(end - i == 0)
		new_token->content = NULL;
	else
		new_token->content = ft_substr(line,i,end-i);
	token_add_back(tokens, new_token);
	return (end);
}

int check_les_chevrons(char *line, int i)
{
	if(line[i] == '<' || line[i] == '>')
		return (0);
	if(line[i] == '(' || line[i] == ')')
		return (0);
	if(line[i] == ';')
		return (0);
	return (1);
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
	while(line[end] && line[end] != ' ' && check_les_chevrons(line, end))
		end ++;
	new_token = create_token();
	new_token->type = REDIR_IN;
	if(end - i == 0)
		new_token->content = NULL;
	else
		new_token->content = ft_substr(line,i,end-i);
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
	new_token->content = NULL;
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
		if(end - i == 0)
			new_token->content = NULL;
		else
			new_token->content = ft_substr(line, i, end - i);
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
	while(line[end] != ' ' && line[end])
		end++;
	substr = ft_substr(line,i,end-i);
	if (ms_strcmp("echo",substr))
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

void delete_tokens(s_token **tokens)
{
	s_token *current;
	s_token *next;

	if(!tokens)
		return ;
	current = *tokens;
	while(current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	return ;
}
