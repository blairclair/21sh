/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 16:07:12 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/07 16:07:22 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

int		get_s_num(long long n)
{
	int	i;

	if (n < 0)
		i = 3;
	else
		i = 2;
	while ((n = n / 10))
		i++;
	i--;
	return (i);
}

char	*ft_ltoa(long long n)
{
	char	*str;
	int		size;
	int		neg;
	char	*str2;

	neg = 1;
	if (n == '\0')
		return ("0");
	size = get_s_num(n);
	str = malloc(size);
	if (n < 0)
		neg = -1;
	str[size--] = '\0';
	while (n)
	{
		str[size--] = neg * (n % 10) + '0';
		n = n / 10;
	}
	if (neg == -1)
		str[size--] = '-';
	str2 = str;
	free(str);
	return (str2);
}
