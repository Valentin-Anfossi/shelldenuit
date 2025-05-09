/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:23:30 by vanfossi          #+#    #+#             */
/*   Updated: 2025/05/09 14:24:32 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_cd(t_job *j, t_shell *s)
{
	if (j->args[2])
	{
		perror("cd: too many arguments");
		return ;
	}
	if (opendir(j->args[1]))
	{
		printf(j->args[1]);
	}
}