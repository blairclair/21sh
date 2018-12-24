/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ststrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 17:47:31 by agrodzin          #+#    #+#             */
/*   Updated: 2018/03/21 19:31:31 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		first(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'))
	{
		count++;
		i++;
	}
	return (count);
}

int		last(char *str)
{
	int		i;
	int		count;
	int		len;

	len = ft_strlen(str);
	i = len - 1;
	if (len == 0)
		return (0);
	count = 0;
	while (i > 0 && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'))
	{
		count++;
		i--;
	}
	return (count);
}

char	*ft_strtrim(char *s)
{
	char	*str;
	int		i;
	int		j;
	int		end;
	int		len;

	i = first(s);
	end = last(s);
	len = ft_strlen(s);
	if (len - i <= 0)
		return (ft_strdup(""));
	j = 0;
	str = ft_strnew(len - i - end);
	if (!str)
		return (NULL);
	while (s[i] != '\0' && i < len - end)
	{
		str[j] = s[i];
		i++;
		j++;
	}
	return (str);
}
