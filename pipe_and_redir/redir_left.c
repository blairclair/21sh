/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_left.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 11:33:14 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/23 11:33:33 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

int		left_to_right(t_execute *cmdlist, t_env_vars *env_vars)
{
	int fd;
	int fd2;

	fd = open(cmdlist->next->data[0], O_RDONLY, S_IRUSR | S_IWUSR);
	if (cmdlist->next->next->type == REDIR1RIGHT)
		fd2 = open(cmdlist->next->next->next->data[0],
				O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	else if (cmdlist->next->next->type == REDIR2RIGHT)
		fd2 = open(cmdlist->next->next->next->data[0],
				O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if (fd < 0)
	{
		ft_printf("invalid file\n");
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(fd2, STDOUT_FILENO);
	close(fd2);
	get_bfunc(cmdlist->prev->data, env_vars);
	return (1);
}

int		redir_left(t_execute *cmdlist, t_env_vars *env_vars)
{
	int fd;
	int save_in;

	fd = 0;
	if (cmdlist->next->data)
	{
		save_in = dup(STDIN_FILENO);
		fd = open(cmdlist->next->data[0], O_RDONLY, S_IRUSR);
		if (fd < 0)
		{
			ft_printf("invalid file\n");
			return (1);
		}
		dup2(fd, 0);
		close(fd);
		get_bfunc(cmdlist->prev->data, env_vars);
		dup2(save_in, STDIN_FILENO);
		close(save_in);
	}
	else
		ft_printf("invalid file\n");
	return (1);
}
