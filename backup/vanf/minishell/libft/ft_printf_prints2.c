/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_prints2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:34:11 by vanfossi          #+#    #+#             */
/*   Updated: 2024/12/07 01:09:18 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_usign(va_list ptr)
{
	unsigned int	i;

	i = va_arg(ptr, unsigned int);
	return (ft_putunbr(i));
}

int	ft_print_hexlow(va_list ptr)
{
	char			*hex_base;
	unsigned long	d;
	unsigned int	nb;
	int				len;

	hex_base = "0123456789abcdef";
	nb = va_arg(ptr, unsigned int);
	d = 1;
	len = 0;
	while ((nb / d) >= 16)
		d *= 16;
	while (d > 0)
	{
		ft_putchar_fd(hex_base[(nb / d) % 16], 1);
		d /= 16;
		len ++;
	}
	return (len);
}

int	ft_print_hexup(va_list ptr)
{
	char			*hex_base;
	unsigned long	d;
	unsigned int	nb;
	int				len;

	hex_base = "0123456789ABCDEF";
	nb = va_arg (ptr, unsigned int);
	d = 1;
	len = 0;
	while ((nb / d) >= 16)
		d *= 16;
	while (d > 0)
	{
		ft_putchar_fd(hex_base[(nb / d) % 16], 1);
		d /= 16;
		len ++;
	}
	return (len);
}

int	ft_print_perc(void)
{
	char	c;

	c = '%';
	write(1, &c, 1);
	return (1);
}
