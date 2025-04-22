/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:33:10 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/22 05:19:44 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
	char *line;
	t_token **tokens;
	t_job	**jobs;
	
	while(1)
	{
		line = readline("labonneshell :");
		if(line)
		tokens = create_lst_tokens(line);
		type_tokens(tokens);
		debug_print_tokens(tokens);
		jobs = create_lst_job(tokens);
		debug_print_job(jobs);
	}
}



