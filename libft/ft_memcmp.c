/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 17:48:27 by agrodzin          #+#    #+#             */
/*   Updated: 2018/03/19 16:47:21 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			num;
	unsigned char	*cs1;
	unsigned char	*cs2;

	num = 0;
	cs1 = (unsigned char*)s1;
	cs2 = (unsigned char*)s2;
	while (num < n)
	{
		if (*(cs1 + num) == '\0' && *(cs2 + num) != '\0')
			return (0 - *(cs2 + num));
		if (*(cs1 + num) != '\0' && *(cs2 + num) == '\0')
			return (*(cs1 + num));
		if (*(cs1 + num) != *(cs2 + num))
			return (*(cs1 + num) - *(cs2 + num));
		num++;
	}
	num--;
	return (0);
}
