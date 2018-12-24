/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 10:53:36 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/23 10:53:38 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

int		heredoc_rep_line(char *str)
{
	int		i;
	char	buf2[1024];
	char	*ap;

	i = 0;
	ap = buf2;
	tputs(tgetstr("dl", &ap), 0, ft_charput);
	tputs(tgetstr("cr", &ap), 0, ft_charput);
	ft_printf("heredoc-> ");
	while (i < (int)ft_strlen(str))
	{
		ft_charput(str[i]);
		i++;
	}
	return (1);
}

void	read_heredoc(void)
{
	int		fd;
	char	*buf;

	buf = ft_memalloc(10);
	fd = open(g_termstuff.herestring, O_RDWR | O_CREAT, S_IRUSR
			| S_IWUSR);
	while (read(fd, buf, 5))
	{
		ft_printf("%s", buf);
		ft_bzero(buf, ft_strlen(buf));
	}
	free(buf);
}

int		ctrl_d_heredoc(int fd, char *line, t_execute *cmdlist,
t_env_vars *env_vars)
{
	int		fd2;
	char	*fn;
	int		tmpin;
	int		tmpout;

	tmpin = dup(0);
	tmpout = dup(1);
	fd2 = open(g_termstuff.herestring, O_RDWR | O_CREAT |
	O_TRUNC, S_IRUSR | S_IWUSR);
	fn = get_fn_and_print_line(line, fd);
	fd = open(fn, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	dup2(fd, 0);
	close(fd);
	tputs(tgetstr("do", NULL), 0, ft_charput);
	dup2(fd2, STDOUT_FILENO);
	close(fd2);
	get_bfunc(cmdlist->prev->data, env_vars);
	restore_fd(tmpin, tmpout);
	if (cmdlist->next->next == NULL || clist(cmdlist, 1, 2, SEMICOLON))
		read_heredoc();
	get_first_term();
	free(line);
	free(fn);
	return (1);
}

int		line_ed_heredoc(int fd, char *line, t_execute *cmdlist,
t_env_vars *env_vars)
{
	unsigned long long d;

	d = 0;
	read(0, &d, 6);
	if (d == 4)
		return (ctrl_d_heredoc(fd, line, cmdlist, env_vars));
	else if (d == ENTER)
	{
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		ft_bzero(line, ft_strlen(line));
		ft_printf("\nheredoc->");
	}
	else if (d == BACK)
		line[ft_strlen(line) - 1] = '\0';
	else if (ft_isprint(d))
		line[ft_strlen(line)] = d;
	heredoc_rep_line(line);
	return (20);
}

int		redirtwo_left(t_execute *cmdlist, t_env_vars *env_vars)
{
	int		fd;
	char	fn[50];
	char	*line;

	get_new_term();
	ft_strcpy(fn, getenv("HOME"));
	ft_strcat(fn, "/");
	ft_strcat(fn, ".tmpheredoctmp");
	fd = open(fn, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR
			| S_IWUSR);
	line = ft_memalloc(tgetnum("co") * tgetnum("li"));
	g_termstuff.track = -1;
	if (cmdlist->next->data)
	{
		ft_printf("heredoc->");
		while (1)
		{
			if (line_ed_heredoc(fd, line, cmdlist, env_vars) == 1)
				return (1);
		}
	}
	get_first_term();
	free(line);
	return (1);
}
