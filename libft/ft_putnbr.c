/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/25 18:05:21 by agrodzin          #+#    #+#             */
/*   Updated: 2018/05/22 16:27:25 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	int i;
	int tempnb[10];
	int	check;

	check = 0;
	i = 0;
	if (n == 0)
		ft_putchar('0');
	if (n < -2147483647)
		ft_putstr("-2147483648");
	if (n < 0 && n != -2147483648)
	{
		n = n * -1;
		check = 1;
	}
	while (n > 0 && n != -2147483648)
	{
		tempnb[i] = n % 10;
		n = n / 10;
		i++;
	}
	if (check == 1)
		ft_putchar('-');
	while (--i >= 0 && n != -2147483648)
		ft_putchar('0' + tempnb[i]);
}
