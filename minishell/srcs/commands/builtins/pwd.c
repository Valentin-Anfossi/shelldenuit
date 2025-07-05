/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 02:34:16 by vanfossi          #+#    #+#             */
/*   Updated: 2025/07/05 13:21:12 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	command_pwd(void)
{
	char	*buff;

	buff = getcwd(NULL, PATH_MAX);
	ft_printf("%s\n", buff);
	free(buff);
	return (0);
}
