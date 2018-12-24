/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 16:01:08 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/05 14:58:00 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

void	ft_putstr_min(char *str, struct s_print *flags)
{
	int i;

	i = 0;
	while (i < flags->after_size && str[i])
	{
		ft_putchar(str[i]);
		i++;
		flags->loc++;
	}
}

void	get_big_s(struct s_print *flags, struct s_format *let, va_list vl)
{
	wchar_t		*str;
	int			i;

	i = 0;
	str = va_arg(vl, wchar_t *);
	if (flags->precision == 1)
	{
		ft_putwstr_prec(str, flags);
		let->len = flags->after_size;
	}
	else
	{
		while (str[i])
		{
			ft_putchar(str[i]);
			i++;
			flags->loc++;
		}
		let->len = i;
	}
	if (flags->minus == 1)
	{
		print_minus(let, flags);
	}
}

void	get_format_s(struct s_print *flags, struct s_format *let, va_list vl)
{
	char	*str;

	if (let->s == 1 && flags->l_1 == 1)
	{
		get_big_s(flags, let, vl);
	}
	else if (let->s == 1)
	{
		str = va_arg(vl, char *);
		if (str == 0)
			str = "(null)";
		print_flags(let, flags, '\0', str);
		if (flags->precision == 1)
			ft_putstr_prec(str, flags);
		else if (flags->minus == 1)
			ft_putstr_min(str, flags);
		else
		{
			ft_putstr(str);
			flags->loc += ft_strlen(str);
		}
		print_flags_back(let, flags, 0, str);
	}
}

void	get_format_c(struct s_print *flags, struct s_format *let, va_list vl)
{
	int				c;
	wchar_t			c2;

	c = '\0';
	if (let->c == 1)
	{
		print_flags(let, flags, c, NULL);
		c = va_arg(vl, int);
		if (flags->precision == 1)
			print_just(let, flags, c, NULL);
		ft_putchar(c);
		flags->loc++;
		print_flags_back(let, flags, c, NULL);
	}
	else if (let->c2 == 1)
	{
		c2 = va_arg(vl, wchar_t);
		ft_putchar(c2);
		flags->loc++;
		print_flags_back(let, flags, c2, NULL);
	}
}
