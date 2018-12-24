/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_x2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 15:52:23 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/05 07:55:12 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

void	get_h_x2(struct s_format *let, struct s_print *flags, va_list vl)
{
	intmax_t	num2;

	num2 = (unsigned char)va_arg(vl, intmax_t);
	print_flags(let, flags, 0, ft_ultoa_base(num2, 16));
	ft_putstr(ft_strtoupper(ft_ultoa_base(num2, 16)));
	flags->loc += ft_strlen(ft_ultoa_base(num2, 16));
	print_flags_back(let, flags, 0, ft_ultoa_base(num2, 16));
}

void	get_l_x2(struct s_format *let, struct s_print *flags, va_list vl)
{
	unsigned long long	lnum;

	lnum = va_arg(vl, unsigned long long);
	if (flags->precision == 1)
		print_just(let, flags, lnum, ft_ultoa_base(lnum, 16));
	print_flags(let, flags, 0, ft_ltoa_base(lnum, 16));
	ft_putstr(ft_strtoupper(ft_ultoa_base(lnum, 16)));
	flags->loc += ft_strlen(ft_ultoa_base(lnum, 16));
	print_flags_back(let, flags, 0, ft_ultoa_base(lnum, 16));
}

void	get_jz_x2(struct s_format *let, struct s_print *flags, va_list vl)
{
	intmax_t	num2;

	num2 = (size_t)va_arg(vl, intmax_t);
	print_flags(let, flags, 0, ft_ultoa_base(num2, 16));
	ft_putstr(ft_strtoupper(ft_ultoa_base(num2, 16)));
	flags->loc += ft_strlen(ft_ultoa_base(num2, 16));
	print_flags_back(let, flags, 0, ft_ultoa_base(num2, 16));
}

void	get_reg_x2(struct s_format *let, struct s_print *flags, va_list vl)
{
	unsigned int			num;

	num = va_arg(vl, long);
	if (flags->precision == 1)
		print_just(let, flags, num, ft_ultoa_base(num, 16));
	print_flags(let, flags, 0, ft_ltoa_base(num, 16));
	ft_putstr(ft_strtoupper(ft_ltoa_base(num, 16)));
	flags->loc += ft_strlen(ft_ltoa_base(num, 16));
	print_flags_back(let, flags, 0, ft_ltoa_base(num, 16));
}

void	get_format_x2(struct s_format *let, struct s_print *flags, va_list vl)
{
	if (let->x2 == 1 && flags->h_2 == 1)
		get_h_x2(let, flags, vl);
	else if (let->x2 == 1 && (flags->l_1 == 1 || flags->l_2 == 1))
		get_l_x2(let, flags, vl);
	else if (let->x2 == 1 && (flags->z == 1 || flags->j == 1))
		get_jz_x2(let, flags, vl);
	else if (let->x2 == 1)
		get_reg_x2(let, flags, vl);
}
