/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 15:45:55 by agrodzin          #+#    #+#             */
/*   Updated: 2018/03/17 16:02:26 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*n_list;

	n_list = (t_list*)malloc(sizeof(*n_list));
	if (n_list == NULL)
		return (NULL);
	if (content == NULL)
	{
		n_list->content = NULL;
		n_list->content_size = 0;
	}
	else
	{
		n_list->content_size = content_size;
		n_list->content = malloc(content_size + 1);
		n_list->content = ft_memcpy(n_list->content, content, content_size);
		if (n_list->content == '\0')
		{
			free(n_list);
		}
		n_list->next = NULL;
	}
	return (n_list);
}
