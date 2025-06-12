/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 21:41:04 by vanfossi          #+#    #+#             */
/*   Updated: 2024/11/10 18:58:41 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_splits(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	*ft_make_word(const char *s, int st, char c)
{
	char	*word;
	int		i;
	int		j;
	int		end;

	i = st;
	j = 0;
	end = st;
	while (s[end] && s[end] != c)
		end++;
	word = ft_calloc(sizeof(char), end - st + 1);
	if (!word)
		return (0);
	while (i < end)
	{
		word[j++] = s[i++];
	}
	word[j] = '\0';
	return (word);
}

static void	*ft_freeall(char **strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(strs[i]);
		i ++;
	}
	free(strs);
	return (0);
}

char	**ft_split(const char *s, char c)
{
	char	**array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	array = ft_calloc(sizeof(char *), ft_count_splits(s, c) + 1);
	if (!array)
		return (0);
	while (s[i])
	{
		if (s[i] != c && s[i] != '\0')
		{
			array[j] = ft_make_word(s, i, c);
			if (!array[j])
				return (ft_freeall(array, j));
			while (s[i] && s[i] != c)
				i++;
			j++;
		}
		else
			i++;
	}
	array[j] = 0;
	return (array);
}

// int main(void)
// {
// 	int res1 = ft_count_splits("   bon sjkaldj huw klaskl 9oi  
// klsjkl    jksladj  k llsak  ",' ');
// 	printf("%d\n",res1);
// 	res1 = ft_count_splits("a ",' ');
// 	printf("%d\n",res1);
//  	res1 = ft_count_splits("soadj sjaodja",' ');
// 	printf("%d\n",res1);

// 	char **thebigarrayonhiship = ft_split("   bon sjkaldj huw 
// klaskl 9oi  klsjkl    jksladj  k llsak  ",' ');
// 	int i = 0;
// 	while (thebigarrayonhiship[i])
// {
// 	printf("%s\n",thebigarrayonhiship[i]);
// 	i++;
// }
// }