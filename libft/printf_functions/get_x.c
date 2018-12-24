/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_x.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 15:23:51 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/05 08:03:48 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

void	get_x_h(struct s_format *let, struct s_print *flags, va_list vl)
{
	intmax_t			num2;

	num2 = (unsigned char)va_arg(vl, intmax_t);
	print_flags(let, flags, 0, ft_ultoa_base(num2, 16));
	ft_putstr(ft_ultoa_base(num2, 16));
	flags->loc += ft_strlen(ft_ultoa_base(num2, 16));
	print_flags_back(let, flags, 0, ft_ultoa_base(num2, 16));
}

void	get_x_l(struct s_format *let, struct s_print *flags, va_list vl)
{
	unsigned long long	lnum;

	lnum = va_arg(vl, unsigned long long);
	print_flags(let, flags, 0, ft_ultoa_base(lnum, 16));
	ft_putstr(ft_ultoa_base(lnum, 16));
	flags->loc += ft_strlen(ft_ultoa_base(lnum, 16));
	print_flags_back(let, flags, 0, ft_ultoa_base(lnum, 16));
}

void	get_j_z_x(struct s_format *let, struct s_print *flags, va_list vl)
{
	intmax_t			num2;

	num2 = (size_t)va_arg(vl, intmax_t);
	print_flags(let, flags, 0, ft_ultoa_base(num2, 16));
	ft_putstr(ft_ultoa_base(num2, 16));
	flags->loc += ft_strlen(ft_ultoa_base(num2, 16));
	print_flags_back(let, flags, 0, ft_ultoa_base(num2, 16));
}

void	get_reg_x(struct s_format *let, struct s_print *flags, va_list vl)
{
	unsigned int		num;
	char				*str;

	num = va_arg(vl, long);
	str = ft_ltoa_base(num, 16);
	if (flags->precision == 1)
		print_just(let, flags, num, str);
	print_flags(let, flags, 0, str);
	ft_putstr(str);
	flags->loc += ft_strlen(str);
	print_flags_back(let, flags, 0, str);
}

void	get_format_x(struct s_format *let, struct s_print *flags, va_list vl)
{
	if (let->x == 1 && flags->h_2 == 1)
		get_x_h(let, flags, vl);
	else if (let->x == 1 && (flags->l_1 == 1 || flags->l_2 == 1))
		get_x_l(let, flags, vl);
	else if (let->x == 1 && (flags->z == 1 || flags->j == 1))
		get_j_z_x(let, flags, vl);
	else if (let->x == 1)
		get_reg_x(let, flags, vl);
}
