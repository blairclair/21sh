/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_four.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 21:03:23 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/25 21:03:24 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

char	*update_str2_paste(char *str, char *str2, int i, int k)
{
	k = 1;
	g_termstuff.track = ft_strlen(str2) - 1;
	g_termstuff.changed_len = 1;
	g_termstuff.whole_line_len = ft_strlen(str2);
	str2[i] = '\0';
	reset_highlight(str);
	history_rep_line(str2);
	free(str);
	return (str2);
}

int		islinejustspacetab(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	tputs(tgetstr("up", NULL), 0, ft_charput);
	tputs(tgetstr("dl", NULL), 0, ft_charput);
	tputs(tgetstr("cr", NULL), 0, ft_charput);
	ft_printf("What say you-> ");
	tputs(tgetstr("do", NULL), 0, ft_charput);
	return (1);
}

void	check_quotes(void)
{
	int	quote;

	quote = num_quotes(g_termstuff.origline);
	if (quote)
	{
		if (quote == 2)
		{
			del_character(g_termstuff.origline, '"');
			g_termstuff.origline =
			ft_21_free_first_strjoin(g_termstuff.origline, echo_par(2));
		}
	}
}
