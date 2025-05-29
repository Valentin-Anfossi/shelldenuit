/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 00:38:07 by vanfossi          #+#    #+#             */
/*   Updated: 2025/05/28 16:17:56 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_types(char *form, va_list ptr, int i)
{
	int	count;

	count = 0;
	if (form[i + 1] == 'c')
		count += ft_print_char(ptr);
	else if (form[i + 1] == 's')
		count += ft_print_str(ptr);
	else if (form[i + 1] == 'p')
		count += ft_print_void(ptr);
	else if (form[i + 1] == 'd')
		count += ft_print_dec(ptr);
	else if (form[i + 1] == 'i')
		count += ft_print_int(ptr);
	else if (form[i + 1] == 'u')
		count += ft_print_usign(ptr);
	else if (form[i + 1] == 'x')
		count += ft_print_hexlow(ptr);
	else if (form[i + 1] == 'X')
		count += ft_print_hexup(ptr);
	else if (form[i + 1] == '%' || form[i + 1] == ' ')
		count += ft_print_perc();
	return (count);
}

int	ft_printf_parsing(char *form, va_list ptr)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (i < (int)ft_strlen(form))
	{
		if (form[i] == '%')
		{
			count += ft_printf_types(form, ptr, i);
			i += 2;
		}
		else
		{
			ft_putchar_fd(form[i], 1);
			count ++;
			i++;
		}
	}
	return (count);
}

int	ft_printf(const char *form, ...)
{
	va_list	ptr;
	int		count;

	count = 0;
	va_start (ptr, form);
	count += ft_printf_parsing((char *)form, ptr);
	va_end (ptr);
	return (count);
}

// #define TEST " %x ", -50

// int	main(void)
// {
// 	int		a;
// 	int		b;
// 	a = ft_printf(TEST);
// 	printf("\n");
// 	b = printf(TEST);

// 	printf("\n%d / %d\n", a, b);
// }