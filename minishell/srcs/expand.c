#include "minishell.h"

char	*expand_token_env(char *s, t_shell *shell)
{
	int		i;
	int		j;
	char	*out;
	char	*env;
	char	*to_add;
	char	*temp;

	to_add = (char *)malloc(2);
	out = NULL;
	i = 0;
	j = 0;
	s = ft_strtrim(s,"\"");
	out = ft_strdup ("");

	while (s[i])
	{
		if (s[i] == '$')
		{
			j = i + 1;
			if (s[i + 1] >= '0' && s[i + 1] <= '9')
			{
				i += 2;
				continue ;
			}
			while (ft_isalpha(s[j]) || s[j] == '_')
				j++;
			if (j > i + 1)
			{
				temp = ft_substr(s, i + 1, j - i - 1);
				env = ms_getenv(temp, shell);
				free(temp);
				if (env)
					out = ft_strjoin(out, env);
				i = j - 1;
			}
			else
				out = ft_strjoin(out, "$");
		}
		else
		{
			to_add[0] = s[i];
			to_add[1] = '\0';
			out = ft_strjoin(out, to_add);
		}
		i++;
	}
	return (out);
}

void	check_env(t_token **tokens, t_shell *shell)
{
	t_token	*tok;

	tok = *tokens;
	while (tok)
	{
		tok->content = ft_strtrim(tok->content, "\"'");
		if (tok->type == 7 || tok->type == 1)
		{
			tok->content = expand_token_env(tok->content, shell);
		}
		tok = tok->next;
	}
}