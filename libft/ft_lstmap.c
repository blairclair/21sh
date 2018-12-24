/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 18:58:23 by agrodzin          #+#    #+#             */
/*   Updated: 2018/03/21 15:51:56 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*n_list;
	t_list	*head;

	if (lst == NULL)
		return (n_list = lst);
	n_list = (*f)(lst);
	head = n_list;
	while (lst->next)
	{
		lst = lst->next;
		n_list->next = f(lst);
		n_list = n_list->next;
	}
	return (head);
}
