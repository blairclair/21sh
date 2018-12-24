/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_words.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 15:51:30 by agrodzin          #+#    #+#             */
/*   Updated: 2018/09/20 13:53:56 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

void	mult_row_move_words_left(int pos, int col)
{
	if (pos > col)
	{
		while (pos >= col)
		{
			g_termstuff.row_pos--;
			tputs(tgetstr("up", NULL), 0, ft_charput);
			pos -= col;
		}
	}
	else
	{
		if (g_termstuff.track < (col * (g_termstuff.row_pos - 1)) - 16)
		{
			g_termstuff.row_pos--;
			tputs(tgetstr("up", NULL), 0, ft_charput);
		}
	}
}

void	adjust_rows_move_words_left(int *pos, int *col, int track)
{
	if (g_termstuff.track < *col - 16 && track > (*col * 2) - 16)
	{
		while (g_termstuff.row_pos > 1)
		{
			g_termstuff.row_pos--;
			tputs(tgetstr("up", NULL), 0, ft_charput);
			*pos -= *col;
		}
	}
	if (g_termstuff.row_pos == 2 && g_termstuff.track < *col - 16)
	{
		tputs(tgetstr("up", NULL), 0, ft_charput);
		g_termstuff.row_pos--;
	}
	else if (g_termstuff.row_pos > 2)
		mult_row_move_words_left(*pos, *col);
}

int		move_words_left(char *str)
{
	int	pos;
	int	track;
	int	col;
	int	origpos;

	col = tgetnum("co");
	track = g_termstuff.track;
	origpos = g_termstuff.row_pos;
	while (g_termstuff.track > 0 && str[g_termstuff.track - 1] == ' ')
		g_termstuff.track--;
	while (g_termstuff.track > 0)
	{
		if (g_termstuff.track > 0 && str[g_termstuff.track - 1] == ' ')
			break ;
		g_termstuff.track--;
	}
	if (g_termstuff.track >= 0)
		g_termstuff.track--;
	pos = track - g_termstuff.track;
	adjust_rows_move_words_left(&pos, &col, track);
	return (1);
}

void	something_move_words_right(int *track, int *col, int *pos)
{
	if (g_termstuff.row_pos == 1 && g_termstuff.track >= *col - 16)
	{
		while (*track < g_termstuff.track)
		{
			g_termstuff.row_pos++;
			tputs(tgetstr("do", NULL), 0, ft_charput);
			*track += *col;
		}
	}
	else if (g_termstuff.row_pos > 1)
	{
		*pos = g_termstuff.track - *track;
		while (*pos >= *col)
		{
			g_termstuff.row_pos++;
			tputs(tgetstr("do", NULL), 0, ft_charput);
			*pos -= *col;
		}
		if (g_termstuff.track > (*col * g_termstuff.row_pos) - 16)
		{
			g_termstuff.row_pos++;
			tputs(tgetstr("do", NULL), 0, ft_charput);
		}
	}
}

int		move_words_right(char *str)
{
	int i;
	int check;
	int	col;
	int	track;
	int	pos;

	col = tgetnum("co");
	i = g_termstuff.track;
	track = g_termstuff.track;
	check = 0;
	if (!is_ws(str, i))
		return (1);
	if (i == -1)
		i++;
	if (str[i] && str[i] == ' ')
		i++;
	while (i < (int)ft_strlen(str) && (str[i] == ' ' || check == 0))
	{
		if (str[i] == ' ')
			check = 1;
		i++;
	}
	g_termstuff.track = i - 1;
	something_move_words_right(&track, &col, &pos);
	return (1);
}
