/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 14:13:21 by agrodzin          #+#    #+#             */
/*   Updated: 2018/03/19 16:43:14 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*d;
	size_t	i;

	i = 0;
	d = (char*)b;
	while (i < len)
	{
		d[i] = (unsigned char)c;
		i++;
	}
	i--;
	return (d);
}
