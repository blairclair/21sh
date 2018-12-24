/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_loc_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 14:17:59 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/06 14:18:00 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

int		get_parse_flag_i(const char *format, int i, struct s_print *flags,
		struct s_format *let)
{
	if (parse_flag(format, i, flags))
	{
		if (flags->minus == 1 && flags->zero == 0 &&
				flags->pound == 0 && flags->plus == 0)
		{
			parse_just(format, i, let, flags);
			i = get_size_zer(format, i, flags);
		}
		else if (flags->zero == 1 && flags->minus == 0 &&
				flags->pound == 0 && flags->plus == 0)
		{
			parse_just(format, i, let, flags);
			i = get_size2(format, i, flags);
			i--;
		}
		else
			i++;
	}
	return (i);
}

int		get_parse_size_i(const char *format, int i, struct s_print *flags)
{
	if (parse_size(format, i, flags))
	{
		if (flags->h_2 == 1 || flags->l_2 == 1)
			i += 2;
		else
			i++;
	}
	return (i);
}

int		get_parse_form_i(struct s_print *flags, struct s_format *let,
		va_list vl, int i)
{
	many_formats(flags, let, vl);
	define_values(flags, let);
	define_values2(flags);
	i += 2;
	return (i);
}

int		get_space_i(const char *format, int i, struct s_print *flags)
{
	if (format[i + 1] == ' ' && format[i] == '%')
	{
		flags->space = 1;
		i++;
	}
	return (i);
}

int		get_last_i(const char *format, int i, struct s_print *flags)
{
	if (!ft_isdigit(format[i + 1]) && !parse_flag(format, i, flags)
			&& !parse_size(format, i, flags) && format[i + 1] != '.')
		i++;
	return (i);
}
