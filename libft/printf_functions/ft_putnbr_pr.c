/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_pr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 20:47:51 by agrodzin          #+#    #+#             */
/*   Updated: 2018/05/29 08:49:46 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_pr(int nb, struct s_print *flags)
{
	int min;

	min = 0;
	if (nb < 0)
	{
		ft_putchar('-');
		flags->loc++;
		if (nb == -2147483648)
		{
			min = 1;
			nb = 2147483647;
		}
		else
			nb = nb * -1;
	}
	if (nb >= 10)
	{
		ft_putnbr_pr(nb / 10, flags);
	}
	flags->loc++;
	ft_putchar((nb % 10 + min) + '0');
}
