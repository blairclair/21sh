/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_line_ed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 21:49:46 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/25 21:49:47 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

void	delete_char(void)
{
	int	col;

	col = tgetnum("co");
	if ((g_termstuff.track - 1 == col - 15 && g_termstuff.row_pos == 2) ||
	(g_termstuff.row_pos > 2 && g_termstuff.track - (g_termstuff.row_pos - 1)
	== (col * (g_termstuff.row_pos - 1) - 16)))
		return ;
	if ((g_termstuff.row_pos == 1 && g_termstuff.track >= 0) ||
	(g_termstuff.row_pos == 2 && g_termstuff.track > col - 16) ||
	(g_termstuff.row_pos > 2 &&
	g_termstuff.track > (col * (g_termstuff.row_pos - 1)) - 16))
	{
		if (g_termstuff.rowlen > 1 && g_termstuff.collen == 0)
		{
			g_termstuff.collen = tgetnum("co");
			g_termstuff.rowlen--;
		}
		else
			g_termstuff.collen--;
		g_termstuff.origline = get_del_str(g_termstuff.origline);
		if (g_termstuff.track > -1)
			g_termstuff.track--;
		g_termstuff.whole_line_len--;
	}
	rep_line(g_termstuff.origline);
}

char	*del_chars(char *str, int place)
{
	int	len;

	len = ft_strlen(str);
	while (len > place)
	{
		str[len] = '\0';
		len--;
	}
	return (str);
}

void	del_entire_line(void)
{
	int	col;

	col = tgetnum("co");
	if (g_termstuff.row_pos == 1)
	{
		ft_bzero(g_termstuff.origline, ft_strlen(g_termstuff.origline));
		g_termstuff.track = -1;
		g_termstuff.collen = 15;
		g_termstuff.highlong = 0;
		g_termstuff.highpos = 0;
	}
	else
	{
		del_chars(g_termstuff.origline,
		(col * (g_termstuff.row_pos - 1)) - 16);
		g_termstuff.track = (col * (g_termstuff.row_pos - 1)) - 16;
		rep_line(g_termstuff.origline);
		g_termstuff.row_pos--;
		g_termstuff.rowlen--;
		g_termstuff.delline = 1;
	}
	rep_line(g_termstuff.origline);
}
