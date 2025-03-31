/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:33:10 by vanfossi          #+#    #+#             */
/*   Updated: 2024/11/10 00:36:50 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	ft_intlen(int nbr)
{
	int	len;

	len = 0;
	if (nbr <= 0)
		len = 1;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	unsigned int	nbr;
	int				len;
	char			*string;

	len = ft_intlen(n);
	nbr = n;
	if (n < 0)
		nbr = -n;
	string = malloc(sizeof(char) * len + 1);
	if (!string)
		return (NULL);
	string[len--] = '\0';
	while (len >= 0)
	{
		string[len] = nbr % 10 + '0';
		nbr /= 10;
		len--;
	}
	if (n < 0)
		string[0] = '-';
	return (string);
}

//int main(void)
//{
// 	printf("%s",ft_itoa(42));
// }