/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 08:30:02 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/10 17:45:10 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	char *line;
	
	while(1)
	{
		line = readline("$:");
		add_history(line);
		if(line[0] == '/')
		{
			printf("History cleared.\n");
			rl_clear_history();
		}
		if(line[0] == '.')
		{
			printf("Exiting.\n");
			free(line);
			exit(1);
		}
		rl_replace_line("replaced text", 0);
		printf("%s\n",line);
		rl_redisplay();
	}
}