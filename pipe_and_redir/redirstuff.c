/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirstuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/20 10:15:58 by agrodzin          #+#    #+#             */
/*   Updated: 2018/09/20 10:16:00 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

int		doub_left_to_right(t_execute *cmdlist, t_env_vars *env_vars)
{
	int		fd2;
	int		fd;
	char	*line;

	line = ft_memalloc(10);
	redirtwo_left(cmdlist, env_vars);
	fd = open(g_termstuff.herestring, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	if (cmdlist->next->next->type == REDIR1RIGHT)
		fd2 = open(cmdlist->next->next->next->data[0], O_RDWR |
				O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	else if (cmdlist->next->next->type == REDIR2RIGHT)
		fd2 = open(cmdlist->next->next->next->data[0], O_RDWR |
				O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	while (read(fd, line, 5))
	{
		ft_putstr_fd(line, fd2);
		ft_bzero(line, ft_strlen(line));
	}
	close(fd);
	close(fd2);
	free(line);
	return (1);
}

int		redir_right_fd(t_execute *cmdlist)
{
	int	fd;

	if (cmdlist->type == REDIR1RIGHT)
		fd = open(cmdlist->next->data[0], O_WRONLY | O_CREAT |
		O_TRUNC, S_IRUSR | S_IWUSR);
	else
		fd = open(cmdlist->next->data[0], O_RDWR | O_CREAT |
		O_APPEND, S_IRUSR | S_IWUSR);
	return (fd);
}

void	print_redir_right(int fd, int fdh, char *buf)
{
	int ret;

	while ((ret = read(fdh, buf, 5)))
	{
		buf[ret] = '\0';
		ft_putstr_fd(buf, fd);
		ft_bzero(buf, ft_strlen(buf));
	}
}

int		redir_right(t_execute *cmdlist, t_env_vars *env_vars)
{
	int		fd;
	int		fdh;
	char	buf[6];

	if (cmdlist->next->data)
	{
		fd = redir_right_fd(cmdlist);
		if (clist(cmdlist, 0, 2, REDIR2LEFT))
		{
			fdh = open(g_termstuff.herestring, O_WRONLY | O_CREAT |
			O_APPEND, S_IRUSR | S_IWUSR);
			print_redir_right(fd, fdh, buf);
			close(fd);
			return (1);
		}
		dup2(fd, STDOUT_FILENO);
		get_bfunc(cmdlist->prev->data, env_vars);
		close(fd);
	}
	else
		ft_printf("invalid file\n");
	return (1);
}
