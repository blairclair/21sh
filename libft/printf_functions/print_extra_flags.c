/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_extra_flags.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 13:41:30 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/06 13:41:37 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

void	print_plus(struct s_format *let, struct s_print *flags, int num)
{
	if (let->d == 1 || let->d2 == 1 || let->i == 1)
	{
		if (num >= 0)
		{
			ft_putchar('+');
			flags->loc++;
		}
	}
}

void	print_minus(struct s_format *let, struct s_print *flags)
{
	int	i;
	int	size;

	i = let->len;
	if (flags->before_len > 0)
		size = flags->before_size;
	else
		size = flags->size;
	while (i < size)
	{
		ft_putchar(' ');
		i++;
		flags->loc++;
	}
}

void	print_zero(struct s_format *let, struct s_print *flags)
{
	int	i;

	i = let->len;
	if (flags->plus == 1)
		i++;
	while (i < flags->size)
	{
		ft_putchar('0');
		i++;
		flags->loc++;
	}
}

void	print_pound(struct s_format *let, struct s_print *flags, char *str)
{
	if ((let->x == 1 || let->x2 == 1) && ft_atoi(str) > 0)
	{
		if (let->x == 1)
			ft_putstr("0x");
		else
			ft_putstr("0X");
		flags->loc += 2;
	}
	else if (let->o == 1 || let->o2 == 1)
	{
		if (ft_atoi(str) != 0)
		{
			flags->loc++;
			ft_putchar('0');
		}
	}
}

void	print_space(struct s_format *let, struct s_print *flags, long num)
{
	if (let->d == 1 || let->i == 1)
	{
		if (num >= 0)
		{
			ft_putchar(' ');
			flags->loc++;
		}
	}
	else
	{
		ft_putchar(' ');
		flags->loc++;
	}
}
