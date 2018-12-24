/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes_to_redir.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 10:45:28 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/23 10:45:32 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

int		get_fdout(int outfile, t_execute *cmdlist)
{
	int fdout;

	if (outfile)
	{
		fdout = (cmdlist->type == REDIR1RIGHT) ?
		open(cmdlist->next->data[0], O_RDWR | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR) : open(cmdlist->next->data[0], O_RDWR |
		O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	}
	else
		fdout = dup(STDOUT_FILENO);
	return (fdout);
}

void	wait_for(int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes + 1)
	{
		waitpid(-1, 0, 0);
		i++;
	}
}

void	pipe_to_redir(t_execute *cmdlist, int outfile,
int num_pipes, int fdin)
{
	int fdout;
	int fdpipe[2];
	int i;

	i = -1;
	fdin = dup(STDIN_FILENO);
	while (++i < num_pipes)
	{
		dup2(fdin, 0);
		close(fdin);
		if (i == num_pipes - 1)
			fdout = get_fdout(outfile, cmdlist);
		else
		{
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
		}
		dup2(fdout, 1);
		close(fdout);
		if (fork() == 0)
			execvp(cmdlist->prev->data[0], cmdlist->prev->data);
		cmdlist = cmdlist->next->next;
	}
	wait_for(num_pipes);
}
