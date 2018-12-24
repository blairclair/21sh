/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_rep_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 21:19:32 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/25 21:19:37 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

void	hist_adjust_rows(void)
{
	int	rowlen;

	rowlen = g_termstuff.rowlen;
	if (g_termstuff.prev_row_len == g_termstuff.rowlen)
	{
		while (rowlen > 1)
		{
			tputs(tgetstr("up", NULL), 0, ft_charput);
			rowlen--;
		}
	}
	else
	{
		rowlen = 1;
		if (rowlen < g_termstuff.prev_row_len)
		{
			while (rowlen < g_termstuff.prev_row_len)
			{
				tputs(tgetstr("up", NULL), 0, ft_charput);
				rowlen++;
			}
		}
	}
}

void	hist_single_line(char **tmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (g_termstuff.changed_len > 1)
		hist_adjust_rows();
	tputs(tgetstr("cd", NULL), 0, ft_charput);
	tputs(tgetstr("cr", NULL), 0, ft_charput);
	ft_printf("what say you-> ");
	while (tmp[i])
	{
		if (tmp[i + 1] != NULL)
			ft_printf("%s\n", tmp[i]);
		else
			ft_printf("%s", tmp[i]);
		i++;
	}
}

void	history_rep_line(char *str)
{
	int		col;
	char	**tmp;
	int		i;

	col = tgetnum("co");
	define_values_history_rep_line(col);
	tmp = ft_memalloc(col * g_termstuff.rowlen * sizeof(char *));
	i = 1;
	if (g_termstuff.rowlen == 1)
		tmp[0] = ft_strdup(str);
	else
	{
		tmp[0] = ft_memalloc(col);
		tmp[0] = ft_strncat(tmp[0], str, col - 15);
		g_termstuff.multine += col - 15;
		create_individual_rows(tmp, i, str, col);
	}
	hist_single_line(tmp);
	free_two_d(tmp);
	g_termstuff.prev_row_len = g_termstuff.rowlen;
}
