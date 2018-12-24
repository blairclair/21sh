/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_num_lets.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 14:07:01 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/06 14:07:03 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

void	many_formats(struct s_print *flags, struct s_format *let, va_list vl)
{
	get_format_d(let, flags, vl);
	get_format_d2(let, flags, vl);
	get_format_c(flags, let, vl);
	get_format_s(flags, let, vl);
	get_format_x(let, flags, vl);
	get_format_x2(let, flags, vl);
	get_format_o(let, flags, vl);
	get_format_p(let, flags, vl);
	get_format_u(let, flags, vl);
}

int		check_form(const char *format, int i)
{
	if (format[i + 1] == 'd' || format[i + 1] == 'D' ||
			format[i + 1] == 'c' || format[i + 1] == 's' ||
			format[i + 1] == 'S' || format[i + 1] == 'p' ||
			format[i + 1] == 'i' || format[i + 1] == 'o' ||
			format[i + 1] == 'O' || format[i + 1] == 'u' ||
			format[i + 1] == 'U' || format[i + 1] == 'x' ||
			format[i + 1] == 'X' || format[i + 1] == 'C')
		return (1);
	return (0);
}

int		get_percent(const char *format, int i)
{
	if (format[i] == '-' || format[i] == '+' || format[i] == '0' ||
			format[i] == '#' || format[i] == 'd' || format[i] == 'D' ||
			format[i] == 'c' || format[i] == 's' || format[i] == 'S' ||
			format[i] == 'p' || format[i] == 'i' || format[i] == 'o' ||
			format[i] == 'O' || format[i] == 'u' || format[i] == 'U' ||
			format[i] == 'x' || format[i] == 'X' || format[i] == 'C' ||
			format[i] == 'h' || format[i] == 'l' || format[i] == 'j' ||
			format[i] == 'z')
		return (1);
	return (0);
}
