/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 18:05:37 by agrodzin          #+#    #+#             */
/*   Updated: 2018/03/19 16:42:16 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*n_list;
	t_list	*next1;

	n_list = *alst;
	while (n_list)
	{
		next1 = n_list->next;
		free(n_list);
		(*del)((n_list)->content, (n_list)->content_size);
		n_list = next1;
		*alst = NULL;
	}
}
