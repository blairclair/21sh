/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_aggregation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 10:57:20 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/23 10:57:24 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

void	inner_ag_pipe_redir(int pipefd[2], t_execute *cmdlist,
t_env_vars *env_vars)
{
	pid_t	p1;
	pid_t	p2;

	if ((p1 = fork()) == 0)
	{
		dup2(pipefd[1], STDERR_FILENO);
		close(pipefd[0]);
		get_bfunc(cmdlist->prev->prev->data, env_vars);
		close(pipefd[1]);
		exit(0);
	}
	if ((p2 = fork()) == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
		get_bfunc(cmdlist->next->next->next->next->data, env_vars);
		close(pipefd[0]);
		exit(0);
	}
}

int		redir_ag_right(t_execute *cmdlist, t_env_vars *env_vars,
int bef, int aft)
{
	if (bef != 300 && aft != 300)
	{
		if (bef == 2 && aft == 1)
		{
			dup2(STDERR_FILENO, STDOUT_FILENO);
		}
		else if (bef == 1 && aft == 2)
		{
			dup2(STDOUT_FILENO, STDERR_FILENO);
		}
		if ((cmdlist->next->next->next != NULL &&
					cmdlist->next->next->next->type != PIPE) ||
				(cmdlist->next->next->next == NULL))
			get_bfunc(cmdlist->prev->prev->data, env_vars);
	}
	return (1);
}

int		redir_ag_pipe(t_execute *cmdlist, t_env_vars *env_vars,
int bef, int aft)
{
	int		pipefd[2];
	int		tmpin;
	int		tmpout;

	tmpin = dup(0);
	tmpout = dup(1);
	if (pipe(pipefd) < 0)
	{
		ft_printf("Pipe could not be initialized\n");
		exit(1);
	}
	if (bef != 300 && aft != 300)
		inner_ag_pipe_redir(pipefd, cmdlist, env_vars);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(-1, 0, 0);
	waitpid(-1, 0, 0);
	dup2(tmpout, STDOUT_FILENO);
	dup2(tmpin, STDIN_FILENO);
	close(tmpin);
	close(tmpout);
	return (1);
}
