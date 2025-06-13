/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:09:00 by vanfossi          #+#    #+#             */
/*   Updated: 2024/11/08 16:08:12 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	char	*charsrc;

	charsrc = (char *)src;
	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (i < size -1 && src[i])
	{
		dst[i] = charsrc[i];
		i++;
	}
	if (i < size)
		dst[i] = '\0';
	return (ft_strlen(src));
}

// int main(void)
// {
// 		char dst[10];
// 		char *src = "0123456789";

// 		printf("%d\n",ft_strlcpy(dst,src,11));

// 		printf("%s",dst);
// }