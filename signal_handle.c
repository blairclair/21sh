/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 11:03:02 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/23 11:03:03 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	sighandlec(int i)
{
	char	buf2[1024];
	char	*ap;

	ap = buf2;
	i = 0;
	if (strcmp(g_termstuff.origline, "cat") &&
	ft_strcmp(g_termstuff.origline, "/bin/cat"))
		ft_printf("\nWhat say you->");
	g_termstuff.track = -1;
	g_termstuff.highlong = 0;
	g_termstuff.highpos = 0;
	g_termstuff.collen = 15;
	reset_highlight(g_termstuff.origline);
	save_history(g_termstuff.origline);
	g_termstuff.historypos = g_termstuff.num_hist;
	ft_bzero(g_termstuff.origline, ft_strlen(g_termstuff.origline));
	signal(SIGINT, sighandlec);
	g_termstuff.rowlen = 1;
	g_termstuff.row_pos = 1;
	g_termstuff.num_hist++;
	g_termstuff.delline = 0;
}

void	sighandlewindow(int i)
{
	struct winsize	w;

	i = 0;
	ioctl(0, TIOCGWINSZ, &w);
	g_termstuff.newrow = w.ws_row;
	tputs(tgoto(tgetstr("cm", NULL), 0, g_termstuff.newrow), 0, ft_charput);
}
