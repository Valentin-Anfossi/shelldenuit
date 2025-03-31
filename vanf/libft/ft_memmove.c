/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:33:03 by vanfossi          #+#    #+#             */
/*   Updated: 2024/11/08 16:04:21 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*charsrc;
	char	*chardest;
	size_t	i;

	i = 0;
	charsrc = (char *)src;
	chardest = (char *)dest;
	if (chardest > charsrc)
		while (n-- > 0)
			chardest[n] = charsrc[n];
	else
	{
		while (i < n)
		{
			chardest[i] = charsrc[i];
			i++;
		}
	}
	return (chardest);
}
