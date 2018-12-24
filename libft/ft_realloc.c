/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/29 09:38:33 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/06 16:58:18 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_str_realloc(void *ptr, size_t size)
{
	void	*nptr;

	if (ptr == NULL)
	{
		nptr = malloc(size);
		return (nptr);
	}
	nptr = malloc(size);
	ft_memcpy((char*)nptr, (char*)ptr, sizeof(char*) * ft_strlen(ptr));
	free(ptr);
	return (nptr);
}
