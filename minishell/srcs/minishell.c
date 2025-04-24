/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:33:10 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/24 11:29:21 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//They took er jebs!
void execute_jobs(t_job *jobs)
{
	//do code
		//execute the jerb
			// ... ?
				//success !
}

int main(void)
{
	char *line;
	t_shell *shell;
	t_token **tokens;
	t_job	*jobs;

	while(1)
	{
		line = readline("labonneshell :");
		if(line)
		tokens = create_lst_tokens(line);
		//type_tokens(tokens);
		//debug_print_tokens(tokens);
		jobs = create_job(tokens);
		if(!check_jobs(jobs))
			execute_jobs(jobs);
		debug_print_job(jobs);
		free_jobs(jobs);
	}
}



