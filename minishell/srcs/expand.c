/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:10:08 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/10 20:09:02 by vanfossi         ###   ########.fr       */
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
					free(env);
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
	char	**str;
	char	*out;
	
	i = 0;
	j = 0;
	str = (char **)ft_calloc(5,sizeof(char *));
	while (s[i])
	{
		if (s[i + 1] && s[i] == '$' && s[i + 1] == '?')
		{
			str[1] = ft_substr(s,j,i - j);
			str[2] = ft_itoa(g_exitcode);
			if (str[0])
			{
				str[3] = ft_strjoin(str[0],str[1]);
				free(str[0]);
				str[0] = ft_strjoin(str[3],str[2]);
				free(str[1]);
				free(str[2]);
				free(str[3]);
			}
			else
			{
				str[0] = ft_strjoin(str[1],str[2]);
				free(str[1]);
				free(str[2]);
			}
			i += 2;
			j = i;
			continue ;
		}
		i++;
	}
	if(j < i)
	{
		str[1] = ft_substr(s,j,(i-j));
		str[3] = ft_strjoin(str[0],str[1]);
		free(str[0]);
		free(str[1]);
		out = ft_strdup(str[3]);
		free(str[3]);
	}
	else
	{
		if(str[0])
		{
			out = ft_strdup(str[0]);
			free(str[0]);
		}
		else
			out = ft_strdup("");
	}
	//printf("%s\n",temp);
	free(str);
	return (out);
}



// char	*is_exit_code(char *s, t_shell *shell)
// {
// 	int		i;
// 	int		j;
// 	char	*temp;
// 	char	*out;

// 	// temp = (char *)ft_calloc((ft_strlen(s)
// 	// 			+ ft_get_intlen(g_exitcode)) + 1, 1);
// 	temp = (char *)ft_calloc(9999, 1);
// 	printf("%d\n",ft_get_intlen(g_exitcode));
// 	i = 0;
// 	j = 0;
// 	while (s[i])
// 	{
// 		if (s[i + 1] && s[i] == '$' && s[i + 1] == '?')
// 		{
// 			temp[j] = ft_itoa(g_exitcode);
// 			i = i + 2;
// 			j = j + ft_get_intlen(g_exitcode);
// 			continue ;
// 		}
// 		temp[j] = s[i];
// 		i++;
// 		j++;
// 	}
// 	temp[j] = '\0';
// 	return (temp);
// }

void	check_env(t_token **tokens, t_shell *shell)
{
	t_token	*tok;
	char *tmp;

	tok = *tokens;
	while (tok)
	{
		if (tok->type == DBQ)
		{
			tmp = ft_strtrim(tok->content, "\"");
			free(tok->content);
			tok->content = tmp;
		}
		if (tok->type == SQ)
		{
			tmp = ft_strtrim(tok->content, "'");
			free(tok->content);
			tok->content = tmp;
		}
		if (tok->type == ARG || tok->type == DBQ)
		{
			tmp = is_exit_code(tok->content, shell);
			free(tok->content);
			tok->content = expand_token_env(tmp, shell);
		}
		// else
		// {
		// 	tmp = ft_strdup(tok->content);
		// 	free(tok->content);
		// 	tok->content = tmp;
		// }
		tok = tok->next;
	}
}
