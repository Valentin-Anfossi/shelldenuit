/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 20:34:48 by vanfossi          #+#    #+#             */
/*   Updated: 2024/11/10 00:39:17 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc((sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1)));
	if (!str)
		return (0);
	if (s1)
	{
		while (s1[i])
			str[j++] = s1[i++];
		i = 0;
	}
	if (s2)
	{
		while (s2[i])
			str[j++] = s2[i++];
	}
	str[j] = 0;
	return (str);
}

// int main(void)
// {
// 	char *result = ft_strjoin("  ","sasa");
// 	printf("%s",result);
// 	free(result);
// }