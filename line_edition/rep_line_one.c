/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rep_line_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 22:04:30 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/25 22:04:32 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

void	print_actual_chars(char **tmp, int *i, int *j, int *check)
{
	int	col;

	col = tgetnum("co");
	while (tmp[*i])
	{
		*j = 0;
		while (tmp[*i][*j])
		{
			if (g_termstuff.selected[*check])
			{
				tputs(tgetstr("so", NULL), 0, ft_charput);
				ft_charput(tmp[*i][*j]);
				tputs(tgetstr("se", NULL), 0, ft_charput);
			}
			else
				ft_charput(tmp[*i][*j]);
			(*j)++;
			(*check)++;
		}
		if (tmp[*i] != NULL && g_termstuff.collen >= col)
			tputs(tgetstr("do", NULL), 0, ft_charput);
		(*i)++;
	}
}

void	rep_single_line(char **tmp, int col)
{
	int	i;
	int	j;
	int	check;

	i = 1;
	j = 0;
	check = 0;
	if (g_termstuff.row_pos < g_termstuff.rowlen &&
	g_termstuff.track > (col * g_termstuff.row_pos) - 16)
		g_termstuff.row_pos++;
	i = adjust_for_len(i);
	ft_printf("What say you-> ");
	i = 0;
	print_actual_chars(tmp, &i, &j, &check);
	j = get_lens(tmp);
	i = 0;
	while (i < j - g_termstuff.track - 1)
	{
		tputs(tgetstr("le", NULL), 0, ft_charput);
		i++;
	}
}

void	create_individual_rows(char **tmp, int i, char *str, int col)
{
	while (i < g_termstuff.rowlen)
	{
		tmp[i] = ft_memalloc(col + 1);
		if (i == g_termstuff.rowlen)
			tmp[i] = ft_memmove(tmp[i], str + g_termstuff.multine,
			((int)ft_strlen(str) - g_termstuff.multine));
		else
			tmp[i] = ft_memmove(tmp[i], str + g_termstuff.multine, col);
		tmp[i][ft_strlen(tmp[i])] = '\0';
		g_termstuff.multine += col;
		i++;
	}
	tmp[i] = NULL;
}

int		rep_line(char *str)
{
	int		i;
	int		col;
	char	**tmp;
	int		j;

	col = tgetnum("co");
	tmp = ft_memalloc(col * g_termstuff.rowlen * sizeof(char *));
	define_values_rep_line(&j, &i, str);
	if (g_termstuff.rowlen == 1)
		tmp[0] = ft_strdup(str);
	else
	{
		tmp[0] = ft_memalloc(col);
		tmp[0] = ft_strncat(tmp[0], str, col - 15);
		g_termstuff.multine += col - 15;
		create_individual_rows(tmp, i, str, col);
	}
	rep_single_line(tmp, col);
	free_two_d(tmp);
	g_termstuff.prev_row_len = g_termstuff.rowlen;
	return (1);
}
