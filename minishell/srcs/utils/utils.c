/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:32:34 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/05 17:50:23 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ms_cmdlst(void)
{
	static char	*cmdlst[8];

	cmdlst[0] = "echo";
	cmdlst[1] = "cd";
	cmdlst[2] = "pwd";
	cmdlst[3] = "export";
	cmdlst[4] = "unset";
	cmdlst[5] = "env";
	cmdlst[6] = "exit";
	cmdlst[7] = NULL;
	return (cmdlst);
}

//Compare 2 strings, return 0 = different 1 = same
int	ms_strcmp(char *str1, const char *str2)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (0);
	while (str1[i] && str2[i] && str1[i] == str2[i])
		i++;
	if (i == (int)ft_strlen(str1) && i == (int)ft_strlen(str2))
		return (1);
	else
		return (0);
}

int	ms_lstsize(t_token *lst)
{
	t_token	*list;
	int		i;

	list = lst;
	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}
