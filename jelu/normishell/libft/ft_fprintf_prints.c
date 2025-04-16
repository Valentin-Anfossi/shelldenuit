/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_prints.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:31:59 by vanfossi          #+#    #+#             */
/*   Updated: 2024/12/07 01:41:58 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_fprint_char(va_list ptr, int fd)
{
	char	c;

	c = va_arg (ptr, int);
	write(fd, &c, 1);
	return (1);
}

int	ft_fprint_str(va_list ptr, int fd)
{
	char	*str;

	str = va_arg (ptr, char *);
	if (str)
	{
		ft_putstr_fd(str, fd);
		return (ft_strlen(str));
	}
	else
	{
		ft_putstr_fd("(null)", fd);
		return (6);
	}
}

int	ft_fprint_void(va_list ptr, int fd)
{
	void			*a;
	unsigned long	adr;
	char			*result;
	int				len;

	a = va_arg (ptr, void *);
	if (a == 0)
	{
		ft_putstr_fd("(nil)", fd);
		return (5);
	}
	adr = (unsigned long)a;
	result = ft_itohex(adr);
	ft_putstr_fd("0x", fd);
	ft_putstr_fd(result, fd);
	len = ft_strlen(result) + 2;
	free(result);
	return (len);
}

int	ft_fprint_dec(va_list ptr, int fd)
{
	signed int	nb;
	int			length;

	nb = va_arg(ptr, signed int);
	if (nb == INT_MIN)
	{
		ft_putnbr_fd (INT_MIN, fd);
		return (11);
	}
	length = (ft_get_intlen(nb));
	ft_putnbr_fd(nb, fd);
	return (length);
}

int	ft_fprint_int(va_list ptr, int fd)
{
	int		nb;

	nb = va_arg (ptr, int);
	if (nb == INT_MIN)
	{
		ft_putnbr_fd(INT_MIN, fd);
		return (11);
	}
	ft_putnbr_fd(nb, fd);
	return (ft_get_intlen(nb));
}
