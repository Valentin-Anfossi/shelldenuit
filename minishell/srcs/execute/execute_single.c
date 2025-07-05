/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:54:18 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/05 02:23:07 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ms_execute_single(t_job *j, t_shell *s, t_exec *ex)
{
	//handle_signals_child();
	if(ms_execute_redir(j,ex,0))
	{
		ms_free_ex(ex);
		return (g_exitcode);
	}
	//ms_fix_args(j);
	g_exitcode = select_command(j, s);
	ms_exec_resetredir(j);
	ms_free_ex(ex);
	return (g_exitcode);
}
