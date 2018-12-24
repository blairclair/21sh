/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 17:39:34 by agrodzin          #+#    #+#             */
/*   Updated: 2018/10/22 11:56:50 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

void	edit_line(unsigned long d)
{
	if (d == HIGHLIGHT)
	{
		if (!g_termstuff.highlong)
			g_termstuff.highpos = g_termstuff.track;
		g_termstuff.highlong++;
		move_highlight(g_termstuff.origline);
		rep_line(g_termstuff.origline);
	}
	else if (d == COPKEY)
		ft_copy(g_termstuff.origline);
	else if (d == PASTEKEY)
		g_termstuff.origline = ft_paste(g_termstuff.origline, 0);
	else if (d == CUTKEY)
	{
		g_termstuff.origline = ft_cut(g_termstuff.origline);
		rep_line(g_termstuff.origline);
	}
}

void	check_history(unsigned long d)
{
	if (d == UP)
	{
		if (g_termstuff.historypos > 0)
		{
			g_termstuff.historypos--;
			g_termstuff.origline = get_history_up(g_termstuff.origline);
		}
	}
	else if (d == DOWN)
	{
		if (g_termstuff.historypos < g_termstuff.num_hist)
		{
			g_termstuff.historypos++;
			g_termstuff.origline = get_history_down(g_termstuff.origline);
		}
	}
}

int		line_ed_two(unsigned long d)
{
	if (HISTORY)
		check_history(d);
	else if (LINEMOVE)
		move_cursor_line(d);
	else if (d == DELLINE)
		del_entire_line();
	else
	{
		g_termstuff.collen++;
		g_termstuff.whole_line_len++;
		g_termstuff.origline = get_new_str(g_termstuff.origline, d);
		g_termstuff.track++;
		rep_line(g_termstuff.origline);
	}
	return (1);
}

int		line_ed_one(unsigned long d, t_env_vars *env_vars, t_execute *cmdlist)
{
	int	col;

	col = tgetnum("co");
	if (d == 4 && (int)ft_strlen(g_termstuff.origline) == 0 &&
	cmdlist->type != REDIR2LEFT)
		ft_exit(env_vars);
	if (CHARMOVE)
		move_characters(d, col);
	else if (HOMEEND)
		home_end_keys(d);
	else if (DELETE)
		delete_char();
	else if (WORDMOVE)
		move_words(d);
	else if (EDIT)
		edit_line(d);
	else
		line_ed_two(d);
	return (1);
}
