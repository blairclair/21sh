/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 15:05:39 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/05 08:10:03 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

void	get_l_d(struct s_format *let, struct s_print *flags, va_list vl)
{
	long long		lnum;

	if ((let->d == 1 && (flags->l_2 == 1 || flags->l_1 == 1))
			|| (let->i == 1 && (flags->l_2 == 1 || flags->l_1 == 1)))
	{
		if (flags->l_2 == 1)
			lnum = (long long)va_arg(vl, intmax_t);
		else
			lnum = (long)va_arg(vl, intmax_t);
		print_flags(let, flags, lnum, NULL);
		if (flags->zero == 1 && lnum < 0)
			lnum *= -1;
		ft_putstr(ft_ltoa_base(lnum, 10));
		flags->loc += ft_strlen(ft_ltoa_base(lnum, 10));
		print_flags_back(let, flags, lnum, NULL);
	}
}

void	get_h_d(struct s_format *let, struct s_print *flags, va_list vl)
{
	intmax_t		inum;

	inum = (char)va_arg(vl, int);
	print_flags(let, flags, inum, NULL);
	if (flags->zero == 1 && inum < 0)
		inum *= -1;
	ft_putstr(ft_itoa(inum));
	flags->loc += ft_strlen(ft_itoa(inum));
	print_flags_back(let, flags, inum, NULL);
}

void	get_z_d(struct s_format *let, struct s_print *flags, va_list vl)
{
	intmax_t		inum;

	inum = (size_t)va_arg(vl, intmax_t);
	print_flags(let, flags, inum, NULL);
	if (flags->zero == 1 && inum < 0)
		inum *= -1;
	ft_putstr(ft_ltoa_base(inum, 10));
	flags->loc += ft_strlen(ft_ltoa_base(inum, 10));
	print_flags_back(let, flags, inum, NULL);
}

void	get_j_d(struct s_format *let, struct s_print *flags, va_list vl)
{
	intmax_t		inum;

	inum = va_arg(vl, intmax_t);
	print_flags(let, flags, inum, NULL);
	if (flags->zero == 1 && inum < 0)
		inum *= -1;
	ft_putstr(ft_ltoa_base(inum, 10));
	flags->loc += ft_strlen(ft_ltoa_base(inum, 10));
	print_flags_back(let, flags, inum, NULL);
}

void	get_format_d(struct s_format *let, struct s_print *flags, va_list vl)
{
	if ((let->d == 1 && (flags->l_2 == 1 || flags->l_1 == 1))
			|| (let->i == 1 && (flags->l_2 == 1 || flags->l_1 == 1)))
		get_l_d(let, flags, vl);
	else if ((let->d == 1 && flags->h_2 == 1) ||
			(let->i == 1 && flags->h_2 == 1))
		get_h_d(let, flags, vl);
	else if ((let->d == 1 && flags->z == 1) || (let->i == 1 && flags->z == 1))
		get_z_d(let, flags, vl);
	else if ((let->d == 1 && flags->j == 1) || (let->i == 1 && flags->j == 1))
		get_j_d(let, flags, vl);
	else if (let->d == 1 || let->i == 1)
		get_last_d(let, flags, vl);
}
