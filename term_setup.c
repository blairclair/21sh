/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 22:10:53 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/25 22:11:01 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	get_first_term(void)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_termstuff.oldterm);
}

void	update_values(void)
{
	char					buf[1024];

	tgetent(buf, getenv("TERM"));
	g_termstuff.rowlen = 1;
	g_termstuff.track = -1;
	g_termstuff.row_pos = 1;
	g_termstuff.delline = 0;
	g_termstuff.collen = 15;
	g_termstuff.highlong = 0;
	g_termstuff.highpos = 0;
	g_termstuff.historypos = g_termstuff.num_hist;
	g_termstuff.whole_line_len = 0;
}

void	get_new_term(void)
{
	tcgetattr(STDIN_FILENO, &g_termstuff.oldterm);
	g_termstuff.newterm = g_termstuff.oldterm;
	g_termstuff.newterm.c_lflag &= ~(ICANON | ECHO);
	g_termstuff.newterm.c_cc[VMIN] = 1;
	g_termstuff.newterm.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_termstuff.newterm);
}

int		set_term_environ(void)
{
	char					*name;
	char					buf[1024];
	int						i;

	i = 0;
	name = getenv("TERM");
	if (!name)
	{
		ft_printf("bad terminal environment\n");
		return (-1);
	}
	tgetent(buf, name);
	update_values();
	g_termstuff.track = -1;
	g_termstuff.highlong = 0;
	g_termstuff.highpos = 0;
	g_termstuff.selected = ft_memalloc(tgetnum("co") * tgetnum("li"));
	g_termstuff.historypos = 0;
	g_termstuff.multine = 0;
	g_termstuff.num_hist = 0;
	ft_strcpy(g_termstuff.herestring, getenv("HOME"));
	ft_strcat(g_termstuff.herestring, "/.heredoctmp");
	return (1);
}
