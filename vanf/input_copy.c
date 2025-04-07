/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 05:11:38 by vanfossi          #+#    #+#             */
/*   Updated: 2025/04/04 03:56:27 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main (int argc, char **argv)
{
	if(argc == 2)
	{
		printf("%s",argv[1]);
	}
	else
	{
		char *line;
		line = readline("Line :\n");
		printf("Input :\n%s\n",line);
	}
	return (1);
	
}