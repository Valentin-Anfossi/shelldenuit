/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:26:58 by vanfossi          #+#    #+#             */
/*   Updated: 2024/11/11 14:08:18 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	d;

	d = c;
	i = 0;
	while (s[i])
	{
		if (s[i] == d)
			return ((char *)s + i);
		i++;
	}
	if (d == '\0')
	{
		return ((char *)s + i);
	}
	return (0);
}

// int main (void)
// {
// 	printf("%s", ft_strchr("bonjour",'j'));
// }cd 