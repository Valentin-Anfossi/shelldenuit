/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 21:31:38 by vanfossi          #+#    #+#             */
/*   Updated: 2024/11/10 00:40:13 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_char_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		st;
	int		en;
	int		i;
	char	*string;

	st = 0;
	i = -1;
	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup((char *)s1));
	while (s1[st] && ft_is_char_in_set(s1[st], set))
		st++;
	en = ft_strlen(s1) - 1;
	while (s1[en] && en > st && ft_is_char_in_set(s1[en], set))
		en --;
	string = malloc((en - st + 2) * sizeof(char));
	if (!string)
		return (0);
	while (++i < en - st + 1)
		string[i] = s1[st + i];
	string[i] = '\0';
	return (string);
}

// int main (void)
// {
// 	printf("%s",ft_strtrim(" / sjdakdj    "," /"));
// }