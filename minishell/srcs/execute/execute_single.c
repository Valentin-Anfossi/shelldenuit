/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:54:18 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/15 02:56:24 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_reset_redirs(t_job *j)
{
	if (dup2(j->fd_outfile, STDOUT_FILENO) < 0)
	{
		perror("stdout restore");
		exit(1);
	}
	close(j->fd_outfile);
	if (dup2(j->fd_infile, STDIN_FILENO) < 0)
	{
		perror("stdin restore");
		exit(1);
	}
	close(j->fd_infile);
}

int ms_execute_single(t_job *j, t_shell *s)
{
	if (ms_set_redirs(j))
		return (g_exitcode);
	//ms_fix_args(j);
	g_exitcode = select_command(j, s);
	execute_reset_redirs(j);
	return (1);
}
