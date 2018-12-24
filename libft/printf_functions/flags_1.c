/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 15:02:24 by agrodzin          #+#    #+#             */
/*   Updated: 2018/05/29 15:32:08 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

void	get_format_d2(struct s_format *let, struct s_print *flags, va_list vl)
{
	long long		numl;
	char			*str;

	if (let->d2 == 1)
	{
		numl = va_arg(vl, long long);
		str = ft_ltoa_base(numl, 10);
		print_flags(let, flags, numl, NULL);
		ft_putstr(str);
		flags->loc += ft_strlen(str);
		print_flags_back(let, flags, numl, NULL);
	}
}

void	ft_putstr_prec(char *str, struct s_print *flags)
{
	int	i;
	int	j;
	int	beflen;

	i = 0;
	j = 0;
	if (flags->after_size < (int)ft_strlen(str))
		beflen = flags->before_size - flags->after_size;
	else
		beflen = flags->before_size - (int)ft_strlen(str);
	while (j < beflen)
	{
		ft_putchar(' ');
		j++;
		flags->loc++;
	}
	while (i < flags->after_size)
	{
		if (!str[i])
			break ;
		ft_putchar(str[i]);
		i++;
		flags->loc++;
	}
}

int		ft_wstrlen(wchar_t *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putwstr_prec(wchar_t *str, struct s_print *flags)
{
	int	i;
	int	j;
	int	beflen;

	i = 0;
	j = 0;
	if (flags->after_size < ft_wstrlen(str))
		beflen = flags->before_size - flags->after_size;
	else
		beflen = flags->before_size - ft_wstrlen(str);
	while (j < beflen)
	{
		ft_putchar(' ');
		j++;
		flags->loc++;
	}
	while (i < flags->after_size)
	{
		if (!str[i])
			break ;
		ft_putchar(str[i]);
		i++;
		flags->loc++;
	}
}
