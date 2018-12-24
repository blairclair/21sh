/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 21:15:38 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/25 21:15:40 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

void	move_words(unsigned long d)
{
	if (d == WORDLEFT)
		move_words_left(g_termstuff.origline);
	if (d == WORDRIGHT)
		move_words_right(g_termstuff.origline);
	rep_line(g_termstuff.origline);
}

void	move_char_left(int col)
{
	if (g_termstuff.row_pos == 1 || g_termstuff.row_pos == 2)
	{
		if ((g_termstuff.track >= 0 && g_termstuff.row_pos == 1) ||
		(g_termstuff.row_pos == 2 && g_termstuff.track > (col *
		(g_termstuff.row_pos - 1)) - 16))
			g_termstuff.track--;
	}
	else
	{
		if (g_termstuff.track > (col * (g_termstuff.row_pos - 1)) - 16)
			g_termstuff.track--;
	}
}

void	move_char_right(int col)
{
	if (g_termstuff.track < (int)ft_strlen(g_termstuff.origline) - 1)
	{
		if (g_termstuff.row_pos == 1 && g_termstuff.track < col - 16)
			g_termstuff.track++;
		else if (g_termstuff.row_pos > 1 && g_termstuff.track <
		(col * (g_termstuff.row_pos) - 17))
			g_termstuff.track++;
	}
}

void	move_characters(unsigned long d, int col)
{
	if (d == LEFT)
		move_char_left(col);
	else if (d == RIGHT)
		move_char_right(col);
	rep_line(g_termstuff.origline);
}

void	home_end_keys(unsigned long d)
{
	if (d == F5)
	{
		g_termstuff.track = -1;
		while (g_termstuff.row_pos > 1)
		{
			tputs(tgetstr("up", NULL), 0, ft_charput);
			g_termstuff.row_pos--;
		}
	}
	else if (d == F6)
	{
		while (g_termstuff.row_pos < g_termstuff.rowlen)
		{
			tputs(tgetstr("do", NULL), 0, ft_charput);
			g_termstuff.row_pos++;
		}
		g_termstuff.track = (int)ft_strlen(g_termstuff.origline) - 1;
	}
	rep_line(g_termstuff.origline);
}
