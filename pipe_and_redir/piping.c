/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 15:03:43 by agrodzin          #+#    #+#             */
/*   Updated: 2018/09/27 11:16:35 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

int		get_num_pipes(t_execute *cmdlist)
{
	int	i;

	i = 1;
	if ((cmdlist->type == PIPE && cmdlist->prev->prev != NULL &&
	cmdlist->prev->prev->type != PIPE) || cmdlist->prev->prev == NULL)
	{
		while (cmdlist != NULL)
		{
			if (cmdlist->next->next != NULL &&
			cmdlist->next->next->type == PIPE)
			{
				i++;
				cmdlist = cmdlist->next->next;
			}
			else
				return (i);
		}
	}
	return (i);
}

void	piped_args_heredoc_func(int pipefd[2], t_execute *cmdlist,
t_env_vars *env_vars)
{
	if (fork() == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
		get_bfunc(cmdlist->next->next->next->data, env_vars);
		close(pipefd[0]);
		exit(0);
	}
}

int		piped_args_heredoc(t_execute *cmdlist, t_env_vars *env_vars)
{
	int		pipefd[2];
	int		fd;
	char	*buf2;

	fd = open(g_termstuff.herestring, O_RDWR | O_CREAT |
	O_TRUNC, S_IRUSR | S_IWUSR);
	buf2 = ft_memalloc(500);
	redirtwo_left(cmdlist, env_vars);
	if (pipe(pipefd) < 0)
		exit(1);
	while (read(fd, buf2, 5))
	{
		ft_putstr_fd(buf2, pipefd[1]);
		ft_bzero(buf2, ft_strlen(buf2));
	}
	piped_args_heredoc_func(pipefd, cmdlist, env_vars);
	close(pipefd[0]);
	close(pipefd[1]);
	close(fd);
	waitpid(-1, 0, 0);
	free(buf2);
	return (1);
}

int		piped_args(t_env_vars *env_vars, char **args1, char **args2, int fd)
{
	int		pipefd[2];

	if (pipe(pipefd) < 0)
		exit(1);
	if (fork() == 0)
	{
		fd == 1 ? dup2(pipefd[1], STDOUT_FILENO) : dup2(pipefd[1], fd);
		close(pipefd[0]);
		get_bfunc(args1, env_vars);
		close(pipefd[1]);
		exit(0);
	}
	if (fork() == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
		get_bfunc(args2, env_vars);
		close(pipefd[0]);
		exit(0);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(-1, 0, 0);
	waitpid(-1, 0, 0);
	return (1);
}
