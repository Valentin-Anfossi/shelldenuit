/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:44:07 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/05 18:22:43 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_token_env(t_token **ts, t_shell *s)
{
	char	*str;
	t_token	*t;

	t = *ts;
	while (t)
	{
		if (t->type == ARG || t->type == DBQ)
		{
			if (ft_strchr(t->content, '$'))
			{
				str = ms_token_expand(t, s);
				free(t->content);
				t->content = str;
			}
		}
		t = t->next;
	}
}

char	*ms_token_fuck(char *out, char *newout)
{
	free(out);
	out = newout;
	return (out);
}

char	*ms_token_expand(t_token *t, t_shell *s)
{
	char	*out;
	char	*new_out;
	int		i;

	i = 0;
	out = ft_strdup("");
	while (t->content && t->content[i])
	{
		if (t->content[i] == '$' && (t->content[i + 1] || t->next))
		{
			new_out = ms_env_get(t->content, out, i, s);
			out = ms_token_fuck(out, new_out);
			i += ms_env_length(t->content + i);
			if (i > (int)ft_strlen(t->content))
				break ;
		}
		else
		{
			new_out = ms_env_append(t->content, out, i);
			out = ms_token_fuck(out, new_out);
			i ++;
		}
	}
	return (out);
}

int	ms_env_length(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '$')
		i ++;
	if (ft_isdigit(str[i]))
		return (i + 1);
	else if (str[i] == '?')
		return (ft_get_intlen(g_exitcode) + 1);
	while (ft_isalpha(str[i]) || str[i] == '_')
		i ++;
	return (i);
}

char	*ms_env_append(char *str, char *out, int i)
{
	char	*temp;
	char	*out2;

	temp = ft_substr(str, i, 1);
	out2 = ft_strjoin(out, temp);
	out = out2;
	free(temp);
	return (out);
}
