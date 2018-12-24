/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/24 11:55:18 by agrodzin          #+#    #+#             */
/*   Updated: 2018/05/24 11:57:08 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		get_len(long long n, int base)
{
	int	i;

	i = 2;
	while ((n = n / base))
		i++;
	i--;
	return (i);
}

static char		*get_str(unsigned long long n, int base)
{
	int		k;
	char	*str;
	char	checkbase[16];

	ft_strcpy(checkbase, "0123456789abcdef\0");
	k = get_len(n, base);
	str = (char*)malloc(200);
	if (str == NULL)
		return (NULL);
	str[k--] = '\0';
	while (n)
	{
		str[k--] = checkbase[n % base];
		n = n / base;
	}
	free(str);
	return (str);
}

char			*ft_ultoa_base(unsigned long long n, int base)
{
	char	*str;

	if (n == 0)
		return ("0");
	str = get_str(n, base);
	return (str);
}
