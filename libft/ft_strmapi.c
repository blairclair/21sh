/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 19:10:06 by agrodzin          #+#    #+#             */
/*   Updated: 2018/03/21 15:54:31 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;
	char	*s1;

	if (s == NULL || f == NULL)
		return (NULL);
	else
	{
		str = (char*)s;
		i = 0;
		s1 = malloc(ft_strlen(s) + 1);
		if (s1 == NULL)
			return (NULL);
		while (s[i])
		{
			s1[i] = (*f)(i, s[i]);
			i++;
		}
		s1[i] = '\0';
	}
	return (s1);
}
