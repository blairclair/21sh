/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 10:40:46 by agrodzin          #+#    #+#             */
/*   Updated: 2018/09/20 13:53:36 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

void	delline_str(char *str)
{
	if (g_termstuff.delline == 1)
	{
		g_termstuff.row_pos++;
		g_termstuff.rowlen++;
		g_termstuff.collen = 0;
		g_termstuff.delline = 0;
		tputs(tgetstr("do", NULL), 0, ft_charput);
	}
	free(str);
}

char	*get_new_str(char *str, char c)
{
	int		col;
	int		i;
	char	*str2;
	int		j;

	col = tgetnum("co");
	j = 0;
	i = -1;
	str2 = ft_memalloc(tgetnum("co") * tgetnum("li"));
	while (++i <= g_termstuff.track)
	{
		str2[i] = str[j];
		j++;
	}
	str2[i] = c;
	i++;
	while (str[j])
	{
		str2[i] = str[j];
		j++;
		i++;
	}
	str2[i] = '\0';
	delline_str(str);
	return (str2);
}

char	*get_del_str(char *str)
{
	int		i;
	char	*str2;

	str2 = ft_strdup(str);
	free(str);
	i = g_termstuff.track;
	while (i < (int)ft_strlen(str2))
	{
		str2[i] = str2[i + 1];
		i++;
	}
	rep_line(str2);
	return (str2);
}
