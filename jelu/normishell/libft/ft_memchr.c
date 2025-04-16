/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:48:26 by vanfossi          #+#    #+#             */
/*   Updated: 2024/11/08 13:35:02 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*chara;
	unsigned char	lec;

	chara = (unsigned char *)s;
	lec = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (*chara == lec)
			return (chara);
		chara++;
		i++;
	}
	return (0);
}

// int main(void)
// {
// 	printf("%s", (char *)ft_memchr("bonjour",'j',4));
// }