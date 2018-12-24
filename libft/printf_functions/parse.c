/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 12:25:56 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/05 14:50:55 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

int	parse_flag(const char *format, int i, struct s_print *flags)
{
	if (format[i + 1] == '\0')
		return (0);
	if (format[i + 1] == '+')
		flags->plus = 1;
	else if (format[i + 1] == '-')
		flags->minus = 1;
	else if (format[i + 1] == '#')
		flags->pound = 1;
	else if (format[i + 1] == '0')
		flags->zero = 1;
	else
		return (0);
	return (1);
}

int	parse_just(const char *format, int i, struct s_format *let,
				struct s_print *flags)
{
	if (format[i] != '.')
	{
		i = get_size(i, format, let, flags);
		flags->before_size = flags->size;
		flags->before_len = let->len;
	}
	if (format[i + 1] == '.' || format[i] == '.')
	{
		if (format[i] == '.')
			i++;
		else
			i += 2;
		i = get_size(i, format, let, flags);
		flags->after_size = flags->size;
		flags->after_len = let->len;
	}
	if (flags->minus != 1)
		flags->precision = 1;
	if (flags->plus == 1 || flags->minus == 1 ||
			flags->zero == 1 || flags->pound == 1)
		return (i - 1);
	if (flags->before_len == 0 && flags->after_len == 0)
		return (i + 2);
	return (i);
}

int	parse_size(const char *format, int i, struct s_print *flags)
{
	if (format[i + 1] == '\0')
		return (0);
	if (format[i + 1] == 'l' && format[i + 2] != 'l')
		flags->l_1 = 1;
	else if (format[i + 1] == 'l' && format[i + 2] == 'l')
		flags->l_2 = 1;
	else if (format[i + 1] == 'h' && format[i + 2] != 'h')
		flags->h_1 = 1;
	else if (format[i + 1] == 'h' && format[i + 2] == 'h')
		flags->h_2 = 1;
	else if (format[i + 1] == 'j')
		flags->j = 1;
	else if (format[i + 1] == 'z')
		flags->z = 1;
	else
		return (0);
	return (1);
}

int	parse_form2(const char *format, int i, struct s_format *let)
{
	if (format[i + 1] == '\0')
		return (0);
	if (format[i + 1] == 'U')
		let->u2 = 1;
	else if (format[i + 1] == 'x')
		let->x = 1;
	else if (format[i + 1] == 'X')
		let->x2 = 1;
	else if (format[i + 1] == 'c')
		let->c = 1;
	else if (format[i + 1] == 'C')
		let->c2 = 1;
	else
		return (0);
	return (1);
}

int	parse_form(const char *format, int i, struct s_format *let)
{
	if (format[i + 1] == '\0')
		return (0);
	if (format[i + 1] == 's')
		let->s = 1;
	else if (format[i + 1] == 'S')
		let->s2 = 1;
	else if (format[i + 1] == 'p')
		let->p = 1;
	else if (format[i + 1] == 'd')
		let->d = 1;
	else if (format[i + 1] == 'D')
		let->d2 = 1;
	else if (format[i + 1] == 'i')
		let->i = 1;
	else if (format[i + 1] == 'o')
		let->o = 1;
	else if (format[i + 1] == 'O')
		let->o2 = 1;
	else if (format[i + 1] == 'u')
		let->u = 1;
	else if (parse_form2(format, i, let))
		let->u = let->u;
	else
		return (0);
	return (1);
}
