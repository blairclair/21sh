/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 14:39:32 by agrodzin          #+#    #+#             */
/*   Updated: 2018/05/02 16:06:46 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*cdst;
	char	*csrc;

	cdst = (char*)dst;
	csrc = (char*)src;
	if (csrc < cdst && csrc + (len - 1) > cdst)
	{
		csrc = csrc + (len - 1);
		cdst = cdst + (len - 1);
		while (len > 0)
		{
			*cdst-- = *csrc--;
			len--;
		}
	}
	else
	{
		while (len > 0)
		{
			*cdst++ = *csrc++;
			len--;
		}
	}
	return (dst);
}
