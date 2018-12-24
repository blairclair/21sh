/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 09:58:44 by agrodzin          #+#    #+#             */
/*   Updated: 2018/03/22 15:26:37 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char*)s1;
	ss2 = (unsigned char*)s2;
	while ((*ss1 != '\0' || *ss2 != '\0') && n > 0)
	{
		if (*ss1 == *ss2)
		{
			ss1 = ss1 + 1;
			ss2 = ss2 + 1;
			n--;
		}
		else
			return (*ss1 - *ss2);
	}
	return (0);
}
