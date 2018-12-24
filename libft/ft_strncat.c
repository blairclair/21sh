/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 19:26:38 by agrodzin          #+#    #+#             */
/*   Updated: 2018/04/29 12:53:24 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *restrict s1, const char *restrict s2, size_t n)
{
	int		i;
	size_t	j;
	size_t	check;

	i = 0;
	j = 0;
	check = 0;
	while (s1[i])
		i++;
	while (s2[check])
		check++;
	while (j < n)
	{
		if (j >= check)
			break ;
		s1[i] = s2[j];
		j++;
		i++;
	}
	s1[i] = '\0';
	i--;
	return (s1);
}
