/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:40:38 by vanfossi          #+#    #+#             */
/*   Updated: 2024/12/07 01:09:14 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_intlen(int nb)
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

int	ft_get_uintlen(unsigned int nb)
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

char	*ft_itohex(unsigned long nb)
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

int	ft_putunbr(unsigned int n)
{
	int	c;
	int	len;

	len = ft_get_uintlen(n);
	if (n > 9)
	{
		ft_putunbr (n / 10);
		ft_putunbr (n % 10);
	}
	else
	{
		c = n + 48;
		write(1, &c, 1);
	}
	return (len);
}
