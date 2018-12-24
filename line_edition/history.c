/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 13:38:19 by agrodzin          #+#    #+#             */
/*   Updated: 2018/09/20 13:53:19 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

void	save_history(char *str)
{
	int			col;

	col = tgetnum("co");
	ft_strcpy(g_history[g_termstuff.num_hist], str);
	g_termstuff.num_hist++;
}

char	*get_history_up(char *str)
{
	char	*str2;

	if (g_termstuff.historypos < 0)
	{
		g_termstuff.historypos++;
		return (str);
	}
	str2 = ft_memalloc(ft_strlen(g_history[g_termstuff.historypos])
	* sizeof(char *) + 1);
	ft_strcpy(str2, g_history[g_termstuff.historypos]);
	g_termstuff.track = ft_strlen(str2) - 1;
	g_termstuff.changed_len++;
	g_termstuff.whole_line_len = ft_strlen(str2);
	free(str);
	history_rep_line(str2);
	rep_line(str2);
	return (str2);
}

char	*get_history_down(char *str)
{
	char	*str2;

	str2 = ft_memalloc(ft_strlen(g_history[g_termstuff.historypos])
	* sizeof(char *) + 1);
	ft_strcpy(str2, g_history[g_termstuff.historypos]);
	g_termstuff.track = ft_strlen(str2) - 1;
	g_termstuff.whole_line_len = ft_strlen(str2);
	g_termstuff.changed_len++;
	free(str);
	history_rep_line(str2);
	rep_line(str2);
	return (str2);
}
