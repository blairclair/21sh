/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 10:23:22 by agrodzin          #+#    #+#             */
/*   Updated: 2018/10/04 10:23:24 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf_functions/ft_printf.h"

void	print_args(char **args)
{
	int		i;
	char	*c;
	int		j;

	c = 0;
	i = -1;
	c = args[0];
	while (c != 0)
		c = args[++i];
	j = -1;
	while (++j < i)
	{
		printf("%s\n", args[j]);
	}
	ft_printf("\n");
}
