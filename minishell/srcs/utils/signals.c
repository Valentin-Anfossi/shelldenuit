/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 10:49:30 by vanfossi          #+#    #+#             */
/*   Updated: 2025/06/14 11:02:11 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static void signal_sigsegv(int sig)
// {
// 	(void)sig;
// 	ft_printf("Segue fault\n");
// 	kill(-1,SIGSEGV);
// 	exit(SIGSEGV);
// }

// static void signal_sigabrt(int sig)
// {	
// 	(void)sig;
// 	ft_printf("abort\n");
// }

static void signal_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	ft_printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void signal_sigquit(int sig)
{
	printf("Minishell exit : babye ! (%d)",sig);
	exit(g_exitcode);
}

void handle_signals_child(void)
{	
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT,SIG_DFL);
}

void handle_signals(void)
{	
	signal(SIGINT, signal_sigint);
	signal(SIGABRT,SIG_IGN);
	signal(SIGQUIT,SIG_IGN);
	//if (g_exitcode)
	//	signal(SIGQUIT,signal_sigquit);	
}

void handle_signals_ign(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGABRT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);	
}
