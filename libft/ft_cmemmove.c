/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmemmove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 13:10:26 by agrodzin          #+#    #+#             */
/*   Updated: 2018/04/29 18:36:17 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_cmemmove(char *cdst, char *csrc, int len)
{
	if (csrc < cdst && csrc + (len - 1) > cdst)
	{
		csrc = csrc + (len - 1);
		cdst = cdst + (len - 1);
		while (len > 0)
		{
			*cdst-- = *csrc--;
			len--;
		}
	}
	else
	{
		while (len > 0)
		{
			*cdst++ = *csrc++;
			len--;
		}
	}
	return (cdst);
}
