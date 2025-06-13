/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:40:38 by vanfossi          #+#    #+#             */
/*   Updated: 2024/12/07 01:47:32 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_fget_intlen(int nb)
{
	int	i;

	i = !nb;
	if (nb < 0)
	{
		nb *= -1;
		i ++;
	}
	while (nb > 0)
	{
		i++;
		nb /= 10;
	}
	return (i);
}

int	ft_fget_uintlen(unsigned int nb)
{
	unsigned int	i;

	i = !nb;
	while (nb > 0)
	{
		i++;
		nb /= 10;
	}
	return (i);
}

char	*ft_fitohex(unsigned long nb)
{
	char			*hex_base;
	char			*result;
	int				len;
	unsigned long	d;
	int				i;

	hex_base = "0123456789abcdef";
	d = 1;
	len = 1;
	i = 0;
	while ((nb / d) >= 16)
	{
		len ++;
		d *= 16;
	}
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (0);
	result[len] = 0;
	while (d > 0)
	{
		result[i++] = hex_base[(nb / d) % 16];
		d /= 16;
	}
	return (result);
}

int	ft_fputunbr(unsigned int n, int fd)
{
	int	c;
	int	len;

	len = ft_fget_uintlen(n);
	if (n > 9)
	{
		ft_fputunbr (n / 10, fd);
		ft_fputunbr (n % 10, fd);
	}
	else
	{
		c = n + 48;
		write(fd, &c, 1);
	}
	return (len);
}
