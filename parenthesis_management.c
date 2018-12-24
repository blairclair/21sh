/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_management.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 22:14:44 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/25 22:14:53 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*line_ed_echpar(unsigned long d, char *line)
{
	if (d == BACK)
		line[ft_strlen(line) - 1] = '\0';
	if (d != BACK && d != ENTER)
		line[ft_strlen(line)] = d;
	echpar_rep_line(line);
	return (line);
}

int		echpar_rep_line(char *str)
{
	int		i;
	char	buf2[1024];
	char	*ap;

	i = 0;
	ap = buf2;
	tputs(tgetstr("dl", &ap), 0, ft_charput);
	tputs(tgetstr("cr", &ap), 0, ft_charput);
	ft_printf("quote> ");
	while (i < (int)ft_strlen(str))
	{
		ft_charput(str[i]);
		i++;
	}
	return (1);
}

char	*echpar_define_values(int *fd)
{
	char	*line;
	char	fn[13];

	ft_strcpy(fn, "/tmp/.echpar");
	line = ft_memalloc(200);
	*fd = open(fn, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	g_termstuff.track = -1;
	ft_printf("\nquote> ");
	return (line);
}

void	print_line_echpar(char *line, int fd)
{
	ft_putstr_fd(line, fd);
	ft_putchar_fd('\n', fd);
	ft_bzero(line, ft_strlen(line));
	ft_printf("\nquote> ");
}

char	*echo_par(int quote_num)
{
	unsigned long	d;
	int				fd;
	char			fn[13];
	char			*line;
	char			*buf;

	ft_strcpy(fn, "/tmp/.echpar");
	line = echpar_define_values(&fd);
	buf = ft_memalloc(200);
	while (1)
	{
		d = 0;
		read(0, &d, 6);
		if (d == ENTER)
		{
			if ((how_many(line, '"') % 2 != 0 && quote_num == 2) ||
			(how_many(line, '\'') % 2 != 0 && quote_num == 1))
				return (quote_is_closed(line, fd, quote_num, buf));
			print_line_echpar(line, fd);
		}
		line = line_ed_echpar(d, line);
	}
	free(line);
	return (buf);
}
