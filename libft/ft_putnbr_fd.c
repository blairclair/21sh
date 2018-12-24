/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 15:31:03 by agrodzin          #+#    #+#             */
/*   Updated: 2018/03/19 16:46:47 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int i;
	int tempnb[10];
	int	check;

	check = 0;
	i = 0;
	if (n == 0)
		ft_putchar_fd('0', fd);
	if (n < -2147483647)
		ft_putstr_fd("-2147483648", fd);
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
		ft_putchar_fd('-', fd);
	while (--i >= 0 && n != -2147483648)
		ft_putchar_fd('0' + tempnb[i], fd);
}
