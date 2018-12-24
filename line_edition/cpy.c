/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 15:06:53 by agrodzin          #+#    #+#             */
/*   Updated: 2018/09/20 13:51:41 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

void	reset_highlight(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		g_termstuff.selected[i] = 0;
		i++;
	}
	g_termstuff.highpos = g_termstuff.track;
}

char	*ft_paste(char *str, int j)
{
	int		i;
	char	*str2;
	int		k;

	k = -1;
	str2 = ft_memalloc(ft_strlen(str) + ft_strlen(g_termstuff.highcpy) + 5);
	i = -1;
	while (++i <= g_termstuff.track)
	{
		str2[i] = str[j];
		j++;
	}
	while (++k < (int)ft_strlen(g_termstuff.highcpy))
	{
		str2[i] = g_termstuff.highcpy[k];
		i++;
	}
	while (str[j])
	{
		str2[i] = str[j];
		i++;
		j++;
	}
	str2 = update_str2_paste(str, str2, i, k);
	return (str2);
}

char	*ft_cut(char *str)
{
	char	*str2;
	int		i;
	int		j;

	j = -1;
	i = 0;
	str2 = ft_memalloc(ft_strlen(str) + 1);
	while (str[i])
	{
		if (g_termstuff.selected[i] == 0)
			str2[++j] = str[i];
		i++;
	}
	str2[j] = '\0';
	ft_copy(str);
	if (!ft_strcmp(str2, ""))
		g_termstuff.track = -1;
	i = 0;
	while (g_termstuff.selected[i])
		i++;
	g_termstuff.collen -= i;
	free(g_termstuff.origline);
	return (str2);
}

void	ft_copy(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (g_termstuff.highcpy)
		ft_bzero(g_termstuff.highcpy, ft_strlen(g_termstuff.highcpy));
	else
		g_termstuff.highcpy = ft_memalloc(ft_strlen(str) + 1);
	while (str[i])
	{
		if (g_termstuff.selected[i] == 1)
		{
			g_termstuff.highcpy[j] = str[i];
			j++;
		}
		i++;
	}
	str[i] = '\0';
	reset_highlight(str);
}

void	move_highlight(char *str)
{
	int		i;
	int		j;
	char	buf2[30];
	char	*ap;

	j = 0;
	i = 0;
	ap = buf2;
	reset_highlight(str);
	g_termstuff.highpos = g_termstuff.track + 1;
	while (str[i])
	{
		if (g_termstuff.highpos == i)
			break ;
		i++;
	}
	while (j < g_termstuff.highlong && str[i])
	{
		g_termstuff.selected[i] = 1;
		i++;
		j++;
	}
}
