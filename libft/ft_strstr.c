/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 18:07:02 by agrodzin          #+#    #+#             */
/*   Updated: 2018/03/22 15:23:06 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strstr(const char *haystack, const char *needle)
{
	char	*h2;
	char	*n2;

	if (*needle == '\0')
		return ((void *)haystack);
	while (*haystack)
	{
		if (*haystack == *needle)
		{
			h2 = (void *)haystack + 1;
			n2 = (void *)needle + 1;
			while (*h2 != '\0' && *n2 != '\0' && *h2 == *n2)
			{
				h2 = h2 + 1;
				n2 = n2 + 1;
			}
			if (*n2 == '\0')
				return ((void *)haystack);
		}
		haystack++;
	}
	return (NULL);
}
