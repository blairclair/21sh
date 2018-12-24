/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   how_many_2d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 09:57:50 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/06 16:54:56 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	how_many2d(char **str, char c)
{
	int i;
	int j;
	int num;

	i = 0;
	j = 0;
	num = 0;
	if (str == NULL || c == '\0')
		return (0);
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == c)
				num++;
			j++;
		}
		i++;
	}
	return (num);
}
