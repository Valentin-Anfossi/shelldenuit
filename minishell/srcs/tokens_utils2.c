#include "minishell.h"

int	is_tok_redir(t_token *t)
{
	if (!t->content)
		return (0);
	else if (ms_strcmp(t->content, ">"))
		return (1);
	else if (ms_strcmp(t->content, ">>"))
		return (1);
	else if (ms_strcmp(t->content, "<"))
		return (1);
	else if (ms_strcmp(t->content, "<<"))
		return (1);
	else
		return (0);
}

int	is_tok_arg(t_token *t)
{
	if(t->type == 0)
	{
		t = t->next;
		return(is_tok_arg(t));
	}
	if (!t)
		return (0);
	if (!is_tok_redir(t) && !is_tok_pipe(t)) // is_tok_cmd vraiment utile ?????
		return (1);
	else
		return (0);
}

int	is_str_exec(char *t)
{
	char	*s;
	int		i;

	i = 0;
	if (t)
	{
		s = ft_strtrim(t, "\"\'");
		while (s[i] == ' ')
			i ++;
		while (s[i] == '.')
			i ++;
		if (s[i] == '/')
			return (1);
		else
			return (0);
	}
	return (0);
}

int	is_tok_cmd(t_token *t)
{
	int	i;

	i = 0;
	while (ms_cmdlst()[i])
	{
		if (ms_strcmp(ms_cmdlst()[i], ft_strtrim(t->content, "\'\"")))
			return (1);
		else if (is_str_exec(t->content))
			return (1);
		i ++;
	}
	return (0);
}


int	is_tok_pipe(t_token *t)
{
	if (ms_strcmp(t->content, "|"))
		return (1);
	else
		return (0);
}

int combiendetoks(t_token **t)
{
	int i;
	t_token *temp;

	i = 0;
	temp = *t;
	while (temp)
	{
		temp = temp->next;
		i ++;
	}
	return (i);
}
