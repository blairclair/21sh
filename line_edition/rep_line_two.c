/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rep_line_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 22:07:32 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/25 22:07:33 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

int		get_lens(char **tmp)
{
	int	i;
	int	num;

	num = 0;
	i = 0;
	while (tmp[i])
	{
		num += ft_strlen(tmp[i]);
		i++;
	}
	return (num);
}

void	adjust_for_len_two(void)
{
	int	j;

	j = g_termstuff.row_pos;
	if (g_termstuff.prev_row_len != g_termstuff.rowlen)
	{
		while (j < g_termstuff.rowlen)
		{
			tputs(tgetstr("up", NULL), 0, ft_charput);
			j++;
		}
	}
}

int		adjust_for_len(int i)
{
	int	j;

	j = g_termstuff.row_pos;
	if (g_termstuff.rowlen == 1)
	{
		tputs(tgetstr("cd", NULL), 0, ft_charput);
		tputs(tgetstr("cr", NULL), 0, ft_charput);
	}
	else
	{
		while (i < g_termstuff.row_pos)
		{
			tputs(tgetstr("up", NULL), 0, ft_charput);
			i++;
		}
		tputs(tgetstr("cd", NULL), 0, ft_charput);
		tputs(tgetstr("cr", NULL), 0, ft_charput);
	}
	adjust_for_len_two();
	return (i);
}
