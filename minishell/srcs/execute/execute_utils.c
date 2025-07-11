/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 00:43:57 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/12 19:26:20 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_all(t_shell *s, t_job *j)
{
	(void)s;
	rl_clear_history();
	exit(j->error);
}

int	is_builtin(char *cmd)
{
	char	**lstcmd;
	int		i;

	lstcmd = ms_cmdlst();
	i = 0;
	while (lstcmd[i] != NULL)
	{
		if (ms_strcmp(lstcmd[i], cmd))
			return (1);
		i++;
	}
	return (0);
}

int	n_jobs(t_job *j)
{
	int		n;
	t_job	*job;

	n = 1;
	job = j;
	while (job->piped_job)
	{
		n++;
		job = job->piped_job;
	}
	return (n);
}
