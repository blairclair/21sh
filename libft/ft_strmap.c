/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 18:45:00 by agrodzin          #+#    #+#             */
/*   Updated: 2018/03/21 15:23:53 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*str;
	int		i;
	char	*s1;

	str = (char*)s;
	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	else
	{
		s1 = malloc(ft_strlen(s) + 1);
		if (s1 == NULL)
			return (NULL);
		while (s[i])
		{
			s1[i] = (*f)(s[i]);
			i++;
		}
		s1[i] = '\0';
	}
	return (s1);
}
