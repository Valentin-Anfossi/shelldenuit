/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:54:18 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/18 18:48:13 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ms_execute_single(t_job *j, t_shell *s)
{
	if(ms_execute_redir(j))
		return (g_exitcode);
	//ms_fix_args(j);
	g_exitcode = select_command(j, s);
	ms_exec_resetredir(j);
	return (1);
}
