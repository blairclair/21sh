/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 09:36:20 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/05 16:07:02 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"
#include <stdio.h>

int		get_loc(const char *format, int i, struct s_print *flags)
{
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (format[i + 1] == '%')
			{
				ft_putchar('%');
				flags->loc++;
				i += 1;
			}
			else
				return (i);
		}
		else
		{
			ft_putchar(format[i]);
			flags->loc++;
		}
		i++;
	}
	return (i);
}

int		rename_later(const char *format, struct s_print *flags,
		struct s_format *let, va_list vl)
{
	int	i;

	i = 0;
	while (format[i])
	{
		i = get_loc(format, i, flags);
		if (format[i] == '\0')
			break ;
		while (format[i])
		{
			i = get_parse_flag_i(format, i, flags, let);
			if ((ft_isdigit(format[i + 1]) && format[i + 1] != '0')
					|| format[i + 1] == '.')
				i = parse_just(format, i, let, flags);
			i = get_parse_size_i(format, i, flags);
			i = get_space_i(format, i, flags);
			if (parse_form(format, i, let))
			{
				i = get_parse_form_i(flags, let, vl, i);
				break ;
			}
			i = get_last_i(format, i, flags);
		}
	}
	return (0);
}

void	define_values2(struct s_print *flags)
{
	flags->size = 0;
	flags->just_size = 0;
	flags->perc = 0;
	flags->before_size = 0;
	flags->before_len = 0;
	flags->after_size = 0;
	flags->after_len = 0;
	flags->precision = 0;
	flags->space = 0;
}

void	define_values(struct s_print *flags, struct s_format *let)
{
	flags->plus = 0;
	flags->minus = 0;
	flags->pound = 0;
	flags->zero = 0;
	flags->l_1 = 0;
	flags->l_2 = 0;
	flags->h_1 = 0;
	flags->h_2 = 0;
	flags->j = 0;
	flags->z = 0;
	let->s = 0;
	let->s2 = 0;
	let->p = 0;
	let->d = 0;
	let->d2 = 0;
	let->i = 0;
	let->o = 0;
	let->o2 = 0;
	let->u = 0;
	let->u2 = 0;
	let->x = 0;
	let->x2 = 0;
	let->c = 0;
	let->c2 = 0;
	let->len = 0;
}

int		ft_printf(const char *format, ...)
{
	va_list			vl;
	struct s_print	flags;
	struct s_format	let;

	let.c = 0;
	flags.loc = 0;
	define_values(&flags, &let);
	define_values2(&flags);
	va_start(vl, format);
	rename_later(format, &flags, &let, vl);
	va_end(vl);
	define_values(&flags, &let);
	define_values2(&flags);
	return (flags.loc);
}
