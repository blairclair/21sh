/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 19:44:18 by agrodzin          #+#    #+#             */
/*   Updated: 2018/04/30 19:00:19 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict s1, const char *restrict s2, size_t n)
{
	char	*yo;
	char	*yo2;
	size_t	l;
	size_t	check;

	l = n + 1;
	yo = s1;
	yo2 = (char*)s2;
	while (*s1 && --l > 0)
		s1++;
	l = s1 - yo;
	check = n - l;
	if (check <= 0)
		return (l + ft_strlen(s2));
	while (*s2)
	{
		if (check > 1)
		{
			*s1++ = *s2;
			check--;
		}
		s2++;
	}
	*s1 = '\0';
	return (l + (s2 - yo2));
}
