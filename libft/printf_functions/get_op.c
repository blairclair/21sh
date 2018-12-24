/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 13:41:03 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/05 14:54:22 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

void	get_big_o(struct s_format *let, struct s_print *flags, va_list vl)
{
	unsigned long long	num;

	num = va_arg(vl, unsigned long long);
	if (flags->precision == 1)
		print_just(let, flags, num, ft_ltoa_base(num, 8));
	print_flags(let, flags, 0, ft_ltoa_base(num, 8));
	flags->loc += ft_strlen(ft_ltoa_base(num, 8));
	ft_putstr(ft_strtoupper(ft_ltoa_base(num, 8)));
	print_flags_back(let, flags, 0, ft_ltoa_base(num, 8));
}

void	get_format_o(struct s_format *let, struct s_print *flags, va_list vl)
{
	unsigned long long	num;
	intmax_t			num2;

	if (let->o == 1 && flags->h_2 == 1)
	{
		num2 = (unsigned char)va_arg(vl, intmax_t);
		print_flags(let, flags, 0, ft_itoa_base(num2, 8));
		flags->loc += ft_strlen(ft_itoa_base(num2, 8));
		ft_putstr(ft_strtoupper(ft_itoa_base(num2, 8)));
		print_flags_back(let, flags, 0, ft_itoa_base(num2, 8));
	}
	else if (let->o == 1)
	{
		num = va_arg(vl, unsigned long long);
		if (flags->precision == 1)
			print_just(let, flags, num, ft_ultoa_base(num, 8));
		print_flags(let, flags, 0, ft_ultoa_base(num, 8));
		flags->loc += ft_strlen(ft_ultoa_base(num, 8));
		ft_putstr(ft_ultoa_base(num, 8));
		print_flags_back(let, flags, 0, ft_ultoa_base(num, 8));
	}
	if (let->o2 == 1)
	{
		get_big_o(let, flags, vl);
	}
}

void	get_format_p(struct s_format *let, struct s_print *flags, va_list vl)
{
	unsigned long long	num2;

	if (let->p == 1)
	{
		num2 = va_arg(vl, unsigned long long);
		if (flags->precision == 1)
			print_just(let, flags, num2, ft_ltoa_base(num2, 16));
		else
			ft_putstr("0x");
		if (num2 == 0)
			ft_putchar('0');
		else
			ft_putstr(ft_ltoa_base(num2, 16));
		flags->loc += ft_strlen(ft_ltoa_base(num2, 16)) + 2;
		print_flags_back(let, flags, num2, ft_ltoa_base(num2, 16));
	}
}

void	get_format_u(struct s_format *let, struct s_print *flags, va_list vl)
{
	intmax_t			num2;
	unsigned long long	num;

	if (let->u == 1 && flags->h_2 == 1)
	{
		num2 = (unsigned char)va_arg(vl, intmax_t);
		ft_putnbr_pr(num2, flags);
	}
	else if (let->u == 1)
	{
		num = va_arg(vl, unsigned long long);
		if (flags->precision == 1)
			print_just(let, flags, num, NULL);
		ft_putulong(flags, num);
	}
	if (let->u2 == 1)
	{
		num = va_arg(vl, unsigned long long);
		if (flags->precision == 1)
			print_just(let, flags, num, NULL);
		ft_putulong(flags, num);
	}
}

void	get_xo_let(struct s_format *let, char *str, struct s_print *flags)
{
	if (flags->before_len > 0 && flags->after_size < (int)ft_strlen(str))
		let->len = flags->after_size;
	else
		let->len = ft_strlen(str);
}
