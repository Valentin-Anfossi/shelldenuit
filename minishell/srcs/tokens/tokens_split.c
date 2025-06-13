/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 10:16:35 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/13 11:35:16 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_token_split(char *line, int start, int end, t_token **tokens)
{
	int	i;

	i = 0;
	i = start;
	while (i <= end)
	{
		if (ms_is_redirpipe(&line[i]))
		{
			ms_token_create(line, start, i, tokens);
			ms_token_create(line, i, i + ms_is_redirpipe(&line[i]), tokens);
			i += (ms_is_redirpipe(&line[i]));
			start = i;
		}
		else if (i == end)
		{
			ms_token_create(line, start, end, tokens);
			i++;
		}
		else
			i ++;
	}
}
int	ms_is_redirpipe(char *line)
{
	if (*line == '>' && *(line + 1) == '>')
		return (2);
	else if (*line == '<' && *(line + 1) == '<')
		return (2);
	else if ((*line == '<') && (*line == '>'))
		return (2);
	else if (*line == '>')
		return (1);
	else if (*line == '<')
		return (1);
	else if (*line == '|' && *(line+1) == '|')
		return (2);
	else if (*line == '&' && *(line + 1) == '&')
		return (2);
	else if (*line == '|')
		return (1);
	else
		return (0);
}
