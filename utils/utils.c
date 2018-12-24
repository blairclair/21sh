/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 14:21:21 by agrodzin          #+#    #+#             */
/*   Updated: 2018/09/20 13:54:40 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

int		ft_charput(int c)
{
	return (write(2, &c, 1));
}

char	*del_character(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	str[i] = '\0';
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}
	return (str);
}

int		num_quotes(char *str)
{
	int i;
	int numsing;
	int numdoub;

	i = 0;
	numsing = 0;
	numdoub = 0;
	while (str[i])
	{
		if (str[i] == '"')
			numdoub++;
		else if (str[i] == '\'')
			numsing++;
		i++;
	}
	if (numdoub % 2 != 0)
		return (2);
	if (numsing % 2 != 0)
		return (1);
	return (0);
}
