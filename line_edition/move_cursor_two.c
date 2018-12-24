/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 21:14:34 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/25 21:14:36 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

void	move_cursor_up(int col)
{
	if ((g_termstuff.row_pos == 2) || g_termstuff.row_pos > 2)
	{
		if (g_termstuff.row_pos == 2 && g_termstuff.track < col)
		{
			g_termstuff.row_pos--;
			g_termstuff.track = col - 17;
			tputs(tgetstr("up", NULL), 0, ft_charput);
		}
		else
		{
			g_termstuff.track -= col;
			g_termstuff.row_pos--;
			tputs(tgetstr("up", NULL), 0, ft_charput);
		}
	}
}

void	move_cursor_down(int col)
{
	if (g_termstuff.row_pos + 1 == g_termstuff.rowlen)
	{
		g_termstuff.track = ft_strlen(g_termstuff.origline) - 1;
		g_termstuff.row_pos++;
		tputs(tgetstr("do", NULL), 0, ft_charput);
	}
	else if (g_termstuff.row_pos < g_termstuff.rowlen)
	{
		g_termstuff.track += col;
		g_termstuff.row_pos++;
		tputs(tgetstr("do", NULL), 0, ft_charput);
	}
}

void	move_cursor_line(unsigned long d)
{
	int	col;

	col = tgetnum("co");
	if (d == UPLINE)
		move_cursor_up(col);
	else if (d == DOWNLINE)
		move_cursor_down(col);
	rep_line(g_termstuff.origline);
}
