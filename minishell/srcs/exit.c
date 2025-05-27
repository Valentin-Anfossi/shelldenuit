/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:51:25 by vanfossi          #+#    #+#             */
/*   Updated: 2025/05/10 16:21:26 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void command_exit(t_job *j, t_shell *s)
{
	//free_jobs(j);
	free_shell(s);
	ft_printf("Bye !\n");
	exit(EXIT_SUCCESS);
}