/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:04:42 by vanfossi          #+#    #+#             */
/*   Updated: 2024/11/08 12:25:12 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	nb;
	int	i;
	int	n;

	n = 1;
	i = 0;
	nb = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
		n *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb * n);
}

// int main(void)
// {
//     printf("%d \n",ft_atoi("  ---++sads1234sad123ads"));
//     printf("%d \n",ft_atoi("  ---98789asd"));
//     printf("%d \n",ft_atoi(""));
//     printf("%d \n",ft_atoi("   123+123456asdsd2128"));
//     printf("\n%d \n",atoi("-1234sad123ads"));
//     printf("%d \n",atoi("-98789asd"));
//     printf("%d \n",atoi(""));
//     printf("%d \n",atoi("123+123456asdsd2128"));
// }
