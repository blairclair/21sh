/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_extra_stuff.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 14:29:36 by agrodzin          #+#    #+#             */
/*   Updated: 2018/06/06 14:29:38 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

int		get_print_just_i(struct s_format *let, struct s_print *flags,
		intmax_t num, char *str)
{
	int	i;

	if (let->d == 1 || let->i == 1 || let->u == 1)
		i = get_num_len(num);
	else if (let->c == 1)
		i = 1;
	else if (let->p == 1)
	{
		if (num == 0)
			i = 3;
		else
			i = ft_strlen(str) + 2;
	}
	else
		i = ft_strlen(str);
	if (flags->space == 1 && flags->after_len == 0)
		i++;
	if (num < 0 && (let->d == 1 || let->i == 1 || let->u == 1))
		i--;
	return (i);
}

void	print_space_min(int i, int zerlen, intmax_t num, struct s_print *flags)
{
	while (i < flags->before_size - (zerlen))
	{
		ft_putchar(' ');
		flags->loc++;
		i++;
	}
	if (num < 0)
	{
		ft_putchar('-');
		flags->loc++;
	}
}

void	print_just_zer(int j, int zerlen, struct s_print *flags)
{
	while (j < zerlen)
	{
		ft_putchar('0');
		flags->loc++;
		j++;
	}
}

void	print_just(struct s_format *let, struct s_print *flags,
		intmax_t num, char *str)
{
	int	i;
	int	j;
	int	k;
	int	zerlen;

	j = 0;
	i = get_print_just_i(let, flags, num, str);
	k = i;
	zerlen = flags->after_size - k;
	if (zerlen < 0)
		zerlen = 0;
	if (num < 0)
		i++;
	print_space_min(i, zerlen, num, flags);
	if (let->p == 1)
	{
		ft_putstr("0x");
		if (flags->after_size > k)
			zerlen += 2;
	}
	print_just_zer(j, zerlen, flags);
}
