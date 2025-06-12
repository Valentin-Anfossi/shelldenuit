/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:44:39 by vanfossi          #+#    #+#             */
/*   Updated: 2024/11/08 16:07:15 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	char	*charsrc;

	charsrc = (char *)src;
	i = ft_strlen(dst);
	j = 0;
	if (size <= i)
		return (size + ft_strlen(src));
	while (charsrc[j] && i + j < (size - 1))
	{
		dst[i + j] = charsrc[j];
		j++;
	}
	dst[i + j] = 0;
	return (i + ft_strlen(src));
}

// int main(void)
// {
// 		char dst[6];
// 		dst[0] = 'a';
// 		dst[1] = 'b';
// 		dst[2] = '\0';
// 		char *src = "012345";

// 		printf("%d\n",(int)ft_strlcat(dst,src,6));

// 		printf("%s",dst);
// }