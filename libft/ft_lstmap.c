/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:36:39 by sarchoi           #+#    #+#             */
/*   Updated: 2021/05/07 20:31:46 by sarchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_head;

	if (!lst)
		return ((t_list *)0);
	new = ft_lstnew(f(lst->content));
	new_head = new;
	if (!new)
	{
		ft_lstclear(&new, del);
		return ((t_list *)0);
	}
	while (lst->next)
	{
		new->next = ft_lstnew(f(lst->next->content));
		if (!(new->next))
		{
			ft_lstclear(&(new->next), del);
			return ((t_list *)0);
		}
		new = new->next;
		lst = lst->next;
	}
	return (new_head);
}
