/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owatanab <owatanab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 00:00:05 by otawatanabe       #+#    #+#             */
/*   Updated: 2023/09/29 17:48:45 by owatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*r;
	t_list	*c;

	if (lst == NULL)
		return (NULL);
	c = ft_lstnew(f(lst -> content));
	r = c;
	lst = lst -> next;
	while (lst && c)
	{
		c -> next = ft_lstnew(f(lst -> content));
		c = c -> next;
		lst = lst -> next;
	}
	if (c == NULL)
		ft_lstclear(&r, del);
	return (r);
}
