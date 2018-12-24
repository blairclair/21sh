/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 20:10:27 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/05 16:18:01 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

int		get_num_len(long num)
{
	int	i;

	i = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		num = num * -1;
		i++;
	}
	while (num > 0)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

int		get_num_len_i(int num)
{
	int	i;

	i = 0;
	if (num == 0)
		return (1);
	if (num < 0)
	{
		num = num * -1;
		i++;
	}
	while (num > 0)
	{
		num = num / 10;
		i++;
	}
	return (i);
}

void	set_let_zer(struct s_format *let, int num, char *str)
{
	if (let->d == 1 || let->i == 1)
		let->len = get_num_len(num);
	else if (let->x == 1 || let->x2 == 1 || let->s == 1)
		let->len = ft_strlen(str);
	else if (let->c == 1)
		let->len = 1;
	else if (let->p == 1)
		let->len = ft_strlen(str) + 2;
}

void	print_flags(struct s_format *let, struct s_print *flags,
		long num, char *str)
{
	if (flags->plus == 1)
		print_plus(let, flags, num);
	if ((flags->zero == 1 && flags->minus == 0))
	{
		set_let_zer(let, num, str);
		if (num < 0)
		{
			ft_putchar('-');
			flags->loc++;
		}
		if (flags->before_len > 0 && flags->after_len > 0)
			print_just(let, flags, num, str);
		else
			print_zero(let, flags);
	}
	if (flags->space == 1)
		print_space(let, flags, num);
	if (flags->pound == 1)
		print_pound(let, flags, str);
	if (flags->zero == 1)
	{
		flags->precision = 0;
	}
}

void	print_flags_back(struct s_format *let,
		struct s_print *flags, long num, char *str)
{
	if (flags->minus == 1)
	{
		if (let->d == 1 || let->i == 1)
		{
			if (flags->l_1 == 1 || flags->l_2 == 1)
				let->len = get_num_len(num);
			else
				let->len = get_num_len_i((int)num);
		}
		else if (let->x == 1 || let->x2 == 1 || let->o2 == 1 || let->o == 1 ||
				let->s == 1 || let->s2 == 1)
			get_xo_let(let, str, flags);
		else if (let->p == 1)
		{
			if (num == 0)
				let->len = 3;
			else
				let->len = 2 + ft_strlen(str);
		}
		else if (let->c == 1)
			let->len = 1;
		print_minus(let, flags);
	}
}
