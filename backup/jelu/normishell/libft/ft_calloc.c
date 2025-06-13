/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:11:29 by vanfossi          #+#    #+#             */
/*   Updated: 2024/11/08 13:25:04 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Test fails when nmenb == 0 and size is neg

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void				*r;
	unsigned long int	s;

	s = nmemb * size;
	if (nmemb != 0 && SIZE_MAX / nmemb < size)
	{
		return (0);
	}
	r = (void *)malloc(s);
	if (r == 0)
		return (r);
	ft_bzero(r, s);
	return (r);
}

// int main (void)
// {
// 	void *test = calloc(0,0);
// 	free(test);
// }