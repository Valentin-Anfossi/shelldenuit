/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:49:51 by vanfossi          #+#    #+#             */
/*   Updated: 2024/11/10 15:49:51 by vanfossi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*n;

	if (!lst || !f || !del)
		return (0);
	list = 0;
	while (lst)
	{
		n = ft_lstnew(f(lst -> content));
		if (!n)
		{
			ft_lstclear(&list, del);
			return (0);
		}
		ft_lstadd_back(&list, n);
		lst = lst->next;
	}
	return (list);
}
