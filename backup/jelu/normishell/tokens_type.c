#include "minishell.h"

//Create a append token containing desired file name
int	token_append(char *line, int i, t_token **tokens)
{
	t_token	*new_token;
	int		end;

	i += 2;
	while (line[i] && line[i] == ' ')
		i ++;
	end = i;
	while (line[end] && line[end] != ' ' && check_les_chevrons(line, end))
		end ++;
	new_token = create_token();
	new_token->type = APPEND;
	if (end - i == 0)
		new_token->content = NULL;
	else
		new_token->content = ft_substr(line, i, end - i);
	token_add_back(tokens, new_token);
	return (end);
}

//Create a heredoc token containing STOP word
int	token_heredoc(char *line, int i, t_token **tokens)
{
	t_token	*new_token;
	int		end;

	i += 2;
	while (line[i] && line[i] == ' ')
		i ++;
	end = i;
	while (line[end] && line[end] != ' ' && check_les_chevrons(line, end))
		end ++;
	new_token = create_token();
	new_token->type = HEREDOC;
	if (end - i == 0)
		new_token->content = NULL;
	else
		new_token->content = ft_substr(line, i, end - i);
	token_add_back(tokens, new_token);
	return (end);
}

//Create a outfile token containing desired file name
int	token_outfile(char *line, int i, t_token **tokens)
{
	t_token	*new_token;
	int		end;

	i ++;
	while (line[i] && line[i] == ' ')
		i ++;
	end = i;
	while (line[end] && line[end] != ' ' && check_les_chevrons(line, end))
		end ++;
	new_token = create_token();
	new_token->type = REDIR_OUT;
	if (end - i == 0)
		new_token->content = NULL;
	else
		new_token->content = ft_substr(line, i, end - i);
	token_add_back(tokens, new_token);
	return (end);
}

//Create a infile token containing relative file path
int	token_infile(char *line, int i, t_token **tokens)
{
	t_token	*new_token;
	int		end;

	i ++;
	while (line[i] && line[i] == ' ')
		i ++;
	end = i;
	while (line[end] && line[end] != ' ' && check_les_chevrons(line, end))
		end ++;
	new_token = create_token();
	new_token->type = REDIR_IN;
	if (end - i == 0)
		new_token->content = NULL;
	else
		new_token->content = ft_substr(line, i, end - i);
	token_add_back(tokens, new_token);
	return (end);
}
