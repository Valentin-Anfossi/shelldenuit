#include "minishell.h"

int	check_tokens_list(t_token **tokens)
{
	t_token	*cur_token;
	int		list_length;

	list_length = ms_lstsize(*tokens);
	cur_token = *tokens;
	if (tokens[0]->type == 2)
		return (ft_printf("%s: command not found\n", tokens[0]->content));
	while (cur_token)
	{
		if (cur_token->type > 2 && cur_token->type < 7 && !cur_token->content)
		{
			if (!cur_token->next)
				return (write(2,
						"minishell : syntax error near unexpected token 'newline'\n", 58));
			else
				cur_token = cur_token->next;
			if (cur_token->type > 2 && cur_token->type < 7)
				return (write(2, "minishell : syntax error near unexpected token ", 48)
					+ write(2, get_error(cur_token->type),
						ft_strlen(get_error(cur_token->type))));
		}
		cur_token = cur_token->next;
	}
	return (0);
}

int	check_les_chevrons(char *line, int i)
{
	if (line[i] == '<' || line[i] == '>')
		return (0);
	if (line[i] == '(' || line[i] == ')')
		return (0);
	if (line[i] == ';')
		return (0);
	return (1);
}

//Checks for commands (nooooo)
int	check_for_commands(char *line, int i)
{
	char	*substr;
	int		end;

	end = i;
	while (line[end] != ' ' && line[end])
		end++;
	substr = ft_substr(line, i, end - i);
	if (ms_strcmp("echo", substr))
		return (10);
	else if (ms_strcmp("cd", substr))
		return (11);
	else if (ms_strcmp("pwd", substr))
		return (12);
	else if (ms_strcmp("export", substr))
		return (13);
	else if (ms_strcmp("unset", substr))
		return (14);
	else if (ms_strcmp("env", substr))
		return (15);
	else if (ms_strcmp("exit", substr))
		return (16);
	else
		return (0);
}
