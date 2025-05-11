/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:16:56 by vanfossi          #+#    #+#             */
/*   Updated: 2025/05/10 18:05:15 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int err_exp_ident(char *str)
{
	ft_printf("minishell: export: '%s': not a valid identifier\n",str);
	return (0);
}

int err_cmd_nfound(char *str)
{
	ft_printf("minishell: %s : command not found\n");
	return (0);
}