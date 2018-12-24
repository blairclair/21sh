/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pipe_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 11:06:08 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/23 11:06:09 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

int		get_fd2_h_to_pipe_to_redir(t_execute *cmdlist)
{
	int	fd2;

	fd2 = 1;
	if (cmdlist->next->next->next->next->type == REDIR1RIGHT)
		fd2 = open(cmdlist->next->next->next->next->next->data[0],
		O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	else if (cmdlist->next->next->next->next->type == REDIR2RIGHT)
		fd2 = open(cmdlist->next->next->next->next->next->data[0],
		O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	return (fd2);
}

void	the_pipe_part(int pipefd[2], int fd2, t_execute *cmdlist,
t_env_vars *env_vars)
{
	if (fork() == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
		dup2(fd2, STDOUT_FILENO);
		close(fd2);
		get_bfunc(cmdlist->next->next->next->data, env_vars);
		close(pipefd[0]);
		exit(0);
	}
}

int		heredoc_to_pipe_to_redir(t_execute *cmdlist, t_env_vars *env_vars)
{
	int		pipefd[2];
	int		fd;
	int		fd2;
	char	*buf2;

	fd = open(g_termstuff.herestring, O_RDWR | O_CREAT |
	O_APPEND, S_IRUSR | S_IWUSR);
	buf2 = ft_memalloc(500);
	redirtwo_left(cmdlist, env_vars);
	fd2 = get_fd2_h_to_pipe_to_redir(cmdlist);
	if (pipe(pipefd) < 0)
		exit(1);
	while (read(fd, buf2, 5))
	{
		ft_putstr_fd(buf2, pipefd[1]);
		ft_bzero(buf2, ft_strlen(buf2));
	}
	the_pipe_part(pipefd, fd2, cmdlist, env_vars);
	close(pipefd[0]);
	close(pipefd[1]);
	close(fd);
	waitpid(-1, 0, 0);
	free(buf2);
	return (1);
}
