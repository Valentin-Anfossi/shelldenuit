/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:49:30 by vanfossi          #+#    #+#             */
/*   Updated: 2025/05/21 10:56:43 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void signal_sigint(void)
{
	printf("\n");
	rl_replace_line("",0);
	rl_on_new_line();
	if(gl_pid == 0)
		rl_redisplay();
}

static void signal_sigsegv(void)
{
	printf("Segmentation fault\n");
	exit(SIGSEGV);
}

static void signal_sigabrt(void)
{
	printf("abort\n");
}

void handle_signals(void)
{
	signal(SIGINT, &signal_sigint);
	signal(SIGSEGV, &signal_sigsegv);
	signal(SIGABRT, &signal_sigabrt);
	signal(SIGQUIT, SIG_IGN);
}