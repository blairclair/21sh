/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 09:47:04 by agrodzin          #+#    #+#             */
/*   Updated: 2018/03/22 15:23:37 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*str;
	size_t	i;

	i = 0;
	if ((str = (void*)malloc(size)))
	{
		ft_bzero(str, size);
		return (str);
	}
	return (NULL);
}
