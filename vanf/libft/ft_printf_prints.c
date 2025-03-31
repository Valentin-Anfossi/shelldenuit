/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_prints.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 18:31:59 by vanfossi          #+#    #+#             */
/*   Updated: 2024/12/07 01:09:23 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_char(va_list ptr)
{
	char	c;

	c = va_arg (ptr, int);
	write(1, &c, 1);
	return (1);
}

int	ft_print_str(va_list ptr)
{
	char	*str;

	str = va_arg (ptr, char *);
	if (str)
	{
		ft_putstr_fd(str, 1);
		return (ft_strlen(str));
	}
	else
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
}

int	ft_print_void(va_list ptr)
{
	void			*a;
	unsigned long	adr;
	char			*result;
	int				len;

	a = va_arg (ptr, void *);
	if (a == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	adr = (unsigned long)a;
	result = ft_itohex(adr);
	ft_putstr_fd("0x", 1);
	ft_putstr_fd(result, 1);
	len = ft_strlen(result) + 2;
	free(result);
	return (len);
}

int	ft_print_dec(va_list ptr)
{
	signed int	nb;
	int			length;

	nb = va_arg(ptr, signed int);
	if (nb == INT_MIN)
	{
		ft_putnbr_fd (INT_MIN, 1);
		return (11);
	}
	length = (ft_get_intlen(nb));
	ft_putnbr_fd(nb, 1);
	return (length);
}

int	ft_print_int(va_list ptr)
{
	int		nb;

	nb = va_arg (ptr, int);
	if (nb == INT_MIN)
	{
		ft_putnbr_fd(INT_MIN, 1);
		return (11);
	}
	ft_putnbr_fd(nb, 1);
	return (ft_get_intlen(nb));
}
