/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:22:01 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/09 14:06:27 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	else
	{
		s3 = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
		if (s3 == NULL)
			return (NULL);
		ft_strcpy(s3, s1);
		ft_strcat(s3, s2);
		while (s3[i])
			i++;
		s3[i] = '\0';
	}
	return (s3);
}
