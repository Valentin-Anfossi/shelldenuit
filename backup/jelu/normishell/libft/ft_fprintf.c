/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 00:38:07 by vanfossi          #+#    #+#             */
/*   Updated: 2024/11/12 00:38:07 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_fprintf_types(char *form, va_list ptr, int i, int fd)
{
	int	count;

	count = 0;
	if (form[i + 1] == 'c')
		count += ft_fprint_char(ptr, fd);
	else if (form[i + 1] == 's')
		count += ft_fprint_str(ptr, fd);
	else if (form[i + 1] == 'p')
		count += ft_fprint_void(ptr, fd);
	else if (form[i + 1] == 'd')
		count += ft_fprint_dec(ptr, fd);
	else if (form[i + 1] == 'i')
		count += ft_fprint_int(ptr, fd);
	else if (form[i + 1] == 'u')
		count += ft_fprint_usign(ptr, fd);
	else if (form[i + 1] == 'x')
		count += ft_fprint_hexlow(ptr, fd);
	else if (form[i + 1] == 'X')
		count += ft_fprint_hexup(ptr, fd);
	else if (form[i + 1] == '%' || form[i + 1] == ' ')
		count += ft_fprint_perc(fd);
	return (count);
}

int	ft_fprintf_parsing(char *form, va_list ptr, int fd)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (i < (int)ft_strlen(form))
	{
		if (form[i] == '%')
		{
			count += ft_fprintf_types(form, ptr, i, fd);
			i += 2;
		}
		else
		{
			ft_putchar_fd(form[i], fd);
			count ++;
			i++;
		}
	}
	return (count);
}

int	ft_fprintf(int fd, const char *form, ...)
{
	va_list	ptr;
	int		count;

	count = 0;
	va_start (ptr, form);
	count += ft_fprintf_parsing((char *)form, ptr, fd);
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