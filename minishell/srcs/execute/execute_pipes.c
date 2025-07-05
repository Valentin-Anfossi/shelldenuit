/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 02:23:48 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/05 18:16:44 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	(*ms_create_pipes(int n))[2]
{
	int	(*pipes)[2];
	int	i;

	if (n == 0)
		return (NULL);
	pipes = (int (*)[2])malloc(n * sizeof(int [2]));
	i = 0;
	if (!pipes)
		return (NULL);
	while (i < n)
	{
		pipe(pipes[i]);
		i ++;
	}
	return (pipes);
}

void	ms_pips_close(int (*pipes)[2], int n, int j)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (i != j -1)
			close(pipes[i][0]);
		if (i != j)
			close(pipes[i][1]);
		i ++;
	}
}

void	ms_pips_closeall(int (*pipes)[2], int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i ++;
	}
}
