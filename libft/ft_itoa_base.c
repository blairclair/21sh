/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:22:50 by agrodzin          #+#    #+#             */
/*   Updated: 2018/05/28 18:10:07 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_len(int n, int base)
{
	int	i;

	i = 0;
	if (n < 0)
		i = 3;
	else
		i = 2;
	while ((n = n / base))
		i++;
	i--;
	return (i);
}

char			*ft_itoa_base(int n, int base)
{
	char	*str;
	int		check;
	int		k;
	char	*checkbase;

	checkbase = malloc(17);
	checkbase = "0123456789abcdef";
	if (n == 0 || n == '\0')
		return ("0");
	check = 1;
	k = get_len(n, base);
	str = malloc(k);
	if (n < 0)
		check = -1;
	str[k--] = '\0';
	while (n)
	{
		str[k--] = checkbase[check * (n % base)];
		n = n / base;
	}
	if (check == -1)
		str[k--] = '-';
	free(str);
	return (str);
}
