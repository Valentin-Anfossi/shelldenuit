/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_prints2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:34:11 by vanfossi          #+#    #+#             */
/*   Updated: 2024/12/07 01:46:28 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_fprint_usign(va_list ptr, int fd)
{
	unsigned int	i;

	i = va_arg(ptr, unsigned int);
	return (ft_fputunbr(i, fd));
}

int	ft_fprint_hexlow(va_list ptr, int fd)
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
		ft_putchar_fd(hex_base[(nb / d) % 16], fd);
		d /= 16;
		len ++;
	}
	return (len);
}

int	ft_fprint_hexup(va_list ptr, int fd)
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
		ft_putchar_fd(hex_base[(nb / d) % 16], fd);
		d /= 16;
		len ++;
	}
	return (len);
}

int	ft_fprint_perc(int fd)
{
	char	c;

	c = '%';
	write(fd, &c, 1);
	return (1);
}
