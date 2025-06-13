/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:37:43 by vanfossi          #+#    #+#             */
/*   Updated: 2024/11/10 00:40:33 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr_helper(void)
{
	char	*subst;

	subst = (char *)malloc(1);
	if (subst == NULL)
		return (NULL);
	subst[0] = '\0';
	return (subst);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*subst;

	i = 0;
	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_substr_helper());
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	subst = malloc(len + 1);
	if (!subst)
		return (0);
	while (s[start] && ((size_t)i < len))
	{
		subst[i] = s[start + i];
		i++;
	}
	subst[i] = 0;
	return (subst);
}

// int main(void)
// {
// 	printf("%s",ft_substr("bonjourwooo",9,4));
// }