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

	// line = create_input_line(line);
t_token	**tokenizer_start(char *line)
{
	t_token	**tokens;
	int		i;

	tokens = create_tokenlst();
	i = 0;
	while (line[i])
	{
		i = tokenizer(line, tokens, i);
		if (i < 0)
		{
			delete_tokens(tokens);
			break ;
		}
	}
	return (tokens);
}

// "" can be a "-n" for echo command ONLY if it's separated by a space
// ie : echo "-n" bou == bou(without newline)
// but : echo "-n"bou == -nbou
// and : echo bou"-n" == bou-n
// "" can be a command, ie: "cd" .. works
// but "cd .." == command not found
// "" can be a path for cd , ie "cd" "vanf" works
// "" cannot be a pipe or >> << < >
// ie : echo bou ">" out == bou > out
// if no space after closing quote == only one arg
// '' is the same except it doesnt expands the env variables in echo

//ENV Variables can contain commands/args/anything
// In case the command is not echo or <<, they should be expanded and tokenized

int	token_env(char *line, int i, t_token **tokens)
{
	t_token	*new_token;
	int		end;

	end = i;
	while (line[end] && line[end] != ' ')
		end ++;
	new_token = create_token();
	new_token->type = ENV;
	if (end - i == 0)
		new_token->content = NULL;
	else
		new_token->content = ft_substr(line, i, end - i);
	token_add_back(tokens, new_token);
	return (end);
}

int	tokenizer_helper(char *line, int i, t_token **tokens)
{
	if (line[i] == '$' && line[i + 1] && line[i + 1] != '?'
		&& line[i + 1] != ' ')
		i = token_env(line, i, tokens);
	else if (line[i] && line[i] != ' ')
		i = token_char(line, i, tokens);
	else
	{
		token_space(tokens);
		i ++;
	}
	return (i);
}

void	token_space(t_token **tokens)
{
	t_token	*new_token;

	new_token = create_token();
	new_token->type = SPC;
	token_add_back(tokens, new_token);
}

//Create a Executable token containing path and adds it to the list
int	token_exec(char *line, int i, t_token **tokens)
{
	t_token	*new_token;
	int		end;

	end = i;
	while (line[end] && line[end] != ' ')
		end ++;
	new_token = create_token();
	new_token->type = CMD;
	if (end - i == 0)
		new_token->content = NULL;
	else
		new_token->content = ft_substr(line, i, end - i);
	token_add_back(tokens, new_token);
	return (end);
}

//Create a pipe token
int	token_pipe(char *line, int i, t_token **tokens)
{
	t_token	*new_token;
	int		end;

	i ++;
	new_token = create_token();
	new_token->type = PIPE;
	new_token->content = NULL;
	token_add_back(tokens, new_token);
	return (i);
}

//Checks if token is a Shell command then create a arg token if not
int	token_char(char *line, int i, t_token **tokens)
{
	t_token	*new_token;
	int		re;
	int		end;

	end = i;
	re = check_for_commands(line, i);
	new_token = create_token();
	while (line[end] && line[end] != ' ')
		end ++;
	if (re)
		new_token->type = re;
	else
	{
		new_token->type = ARG;
		if (end - i == 0)
			new_token->content = NULL;
		else
			new_token->content = ft_substr(line, i, end - i);
	}
	token_add_back(tokens, new_token);
	return (end);
}

int	tokenizer(char *line, t_token **tokens, int i)
{
	if (line[i] == '.' && line[i + 1] && line[i + 1] == '/')
		i = token_exec(line, i, tokens);
	else if (line[i] == '>' && line[i + 1] && line[i + 1] == '>')
		i = token_append(line, i, tokens);
	else if (line[i] == '<' && line[i + 1] && line[i + 1] == '<')
		i = token_heredoc(line, i, tokens);
	else if (line[i] == '>')
		i = token_outfile(line, i, tokens);
	else if (line[i] == '<')
		i = token_infile(line, i, tokens);
	else if (line[i] == '|')
		i = token_pipe(line, i, tokens);
	else if (line[i] == '"' || line[i] == '\'')
		i = token_quotes(line, i, tokens);
	else
		i = tokenizer_helper(line, i, tokens);
	return (i);
}
