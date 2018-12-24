/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sizes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 14:03:45 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/06 14:03:52 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

void	get_last_d(struct s_format *let, struct s_print *flags, va_list vl)
{
	intmax_t		inum;

	inum = (int)va_arg(vl, intmax_t);
	print_flags(let, flags, inum, NULL);
	if (flags->zero == 1 && inum < 0)
		inum *= -1;
	if (flags->precision == 1)
	{
		print_just(let, flags, inum, NULL);
		if (inum < 0)
			inum = inum * -1;
	}
	ft_putnbr_pr(inum, flags);
	print_flags_back(let, flags, inum, NULL);
}

int		get_size(int i, const char *format, struct s_format *let,
		struct s_print *flags)
{
	char	str[40];
	int		j;

	j = 0;
	if (!ft_isdigit(format[i]))
	{
		if (get_percent(format, i + 1))
			return (i + 1);
		while (format[i] && !ft_isdigit(format[i]) && format[i] != '.')
			i++;
	}
	while (ft_isdigit(format[i]) && format[i])
	{
		str[j] = format[i];
		i++;
		j++;
	}
	str[j] = '\0';
	flags->size = ft_atoi(str);
	let->len = j;
	if (flags->pound == 0 && flags->plus == 0 &&
			flags->minus == 0 && flags->zero == 0)
		i--;
	return (i);
}

int		get_size2(const char *format, int i, struct s_print *flags)
{
	char	str[40];
	int		j;

	j = 0;
	if (!ft_isdigit(format[i]))
	{
		if (get_percent(format, i + 1) && format[i + 1] != '-' &&
				format[i + 1] != '0')
			return (i + 1);
		while (format[i] && !ft_isdigit(format[i]))
			i++;
	}
	while (ft_isdigit(format[i]) && format[i])
	{
		str[j] = format[i];
		i++;
		j++;
	}
	str[j] = '\0';
	flags->size = ft_atoi(str);
	if (flags->pound == 0 && flags->plus == 0 && flags->minus == 0
			&& flags->zero == 0)
		i--;
	return (i);
}

int		get_size_zer(const char *format, int i, struct s_print *flags)
{
	char	str[40];
	int		size;

	size = 0;
	while (!ft_isdigit(format[i]) && format[i])
	{
		if (check_form(format, i))
			return (i);
		i++;
	}
	while (ft_isdigit(format[i]))
	{
		str[size] = format[i];
		size++;
		i++;
	}
	flags->size = ft_atoi(str);
	i--;
	return (i);
}
