/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putulong.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 15:47:28 by agrodzin          #+#    #+#             */
/*   Updated: 2018/05/23 15:53:47 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putulong(struct s_print *flags, unsigned long long n)
{
	int i;
	int tempnb[100];

	i = 0;
	if (n == 0)
	{
		flags->loc++;
		ft_putchar('0');
	}
	while (n > 0)
	{
		tempnb[i] = n % 10;
		n = n / 10;
		i++;
	}
	while (--i >= 0)
	{
		ft_putchar('0' + tempnb[i]);
		flags->loc++;
	}
}
