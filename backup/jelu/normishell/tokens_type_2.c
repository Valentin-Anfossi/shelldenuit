#include "minishell.h"

int	token_q(char *line, int i, t_token **tokens)
{
	int		end;
	t_token	*new_token;

	end = i + 1;
	while (line[end])
	{
		if (line[end] == '\'')
		{
			new_token = create_token();
			new_token->type = ARG;
			if (end - i == 0)
				new_token->content = NULL;
			else
				new_token->content = ft_substr(line, i + 1, (end - 1) - i);
			token_add_back(tokens, new_token);
			return (end + 1);
		}
		end++;
	}
	return (token_char(line, i, tokens));
}

int	token_dblq(char *line, int i, t_token **tokens)
{
	int		end;
	t_token	*new_token;

	end = i + 1;
	while (line[end])
	{
		if (line[end] == '"')
		{
			new_token = create_token();
			new_token->type = ARG;
			if (end - i == 0)
				new_token->content = NULL;
			else
				new_token->content = ft_substr(line, i + 1, (end - 1) - i);
			token_add_back(tokens, new_token);
			return (end + 1);
		}
		end++;
	}
	return (token_char(line, i, tokens));
}

int	token_quotes(char *line, int i, t_token **tokens)
{
	if (line[i] == '"')
		i = token_dblq(line, i, tokens);
	else if (line[i] == '\'')
		i = token_q(line, i, tokens);
	return (i);
}
