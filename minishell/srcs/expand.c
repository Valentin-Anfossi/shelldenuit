/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:10:08 by vanfossi          #+#    #+#             */
/*   Updated: 2025/05/09 09:10:12 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_token_env(char *s, t_shell *shell)
{
	int		i;
	int		j;
	char	*out;
	char	*env;
	char	to_add[2];
	char	*temp;

	out = NULL;
	i = 0;
	j = 0;
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
				{
					temp = out;
					out = ft_strjoin(out, env);
					free(temp);
				}
				i = j - 1;
			}
			else
			{
				temp = out;
				out = ft_strjoin(out, "$");
				free(temp);
			}
		}
		else
		{
			to_add[0] = s[i];
			to_add[1] = '\0';
			temp = out;
			out = ft_strjoin(out, to_add);
			free(temp);
		}
		i++;
	}
	free(s);
	return (out);
}

char	*is_exit_code(char *s, t_shell *shell)
{
	int		i;
	int		j;
	char	*temp;

	temp = (char *)ft_calloc((ft_strlen(s)
				+ ft_get_intlen(shell->exit_code)), 1);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i + 1] && s[i] == '$' && s[i + 1] == '?')
		{
			temp = ft_strjoin(temp, ft_itoa(shell->exit_code));
			i = i + 2;
			j = j + ft_get_intlen(shell->exit_code);
			continue ;
		}
		temp[j] = s[i];
		i++;
		j++;
	}
	temp[j] = '\0';
	return (temp);
}

void	check_env(t_token **tokens, t_shell *shell)
{
	t_token	*tok;

	tok = *tokens;
	while (tok)
	{
		if (tok->type == DBQ)
			tok->content = ft_strtrim(tok->content, "\"");
		if (tok->type == SQ)
			tok->content = ft_strtrim(tok->content, "'");
		if (tok->type == 7 || tok->type == 1)
		{
			tok->content = is_exit_code(tok->content, shell);
			tok->content = expand_token_env(tok->content, shell);
		}
		tok = tok->next;
	}
}
