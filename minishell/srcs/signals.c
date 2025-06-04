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

static void signal_sigint(int sig)
{
	(void)sig;
	rl_replace_line("",0);
	ft_printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

static void signal_sigsegv(int sig)
{
	(void)sig;
	ft_printf("Segmentation fault\n");
	exit(SIGSEGV);
}

static void signal_sigabrt(int sig)
{	
	(void)sig;
	ft_printf("abort\n");
}

void handle_signals(void)
{
	signal(SIGINT, signal_sigint);
	signal(SIGSEGV, signal_sigsegv);
//	signal(SIGABRT, signal_sigabrt);
	signal(SIGQUIT, SIG_IGN);
}