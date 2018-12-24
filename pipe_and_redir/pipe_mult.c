/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_mult.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 21:08:34 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/25 21:08:39 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

void		close_pipes(int pipes[], int j)
{
	int k;

	k = 0;
	while (k < j * 2)
	{
		close(pipes[k]);
		k++;
	}
}

t_execute	*update(t_execute *cmdlist, int i, int *in, int *out)
{
	if (cmdlist->next && cmdlist->next->next)
		cmdlist = cmdlist->next->next;
	if (i > 0)
		*in += 2;
	*out += 2;
	return (cmdlist);
}

void		pipe_pipes(int pipes[], int i, int j)
{
	pipe(pipes);
	while (++i < j)
		pipe(pipes + 2 * i);
}

void		end_mult(int pipes[], int j)
{
	int	i;

	close_pipes(pipes, j);
	i = -1;
	while (++i < j + 1)
		waitpid(-1, 0, 0);
}

void		pipe_mult(t_execute *cmdlist, t_env_vars *env_vars, int in, int out)
{
	int pipes[get_num_pipes(cmdlist) * 2];
	int	j;
	int	i;

	cmdlist = define_first_vars(&i, &j, cmdlist, pipes);
	while (++i < j + 1)
	{
		if ((fork()) == 0)
		{
			if (clist(cmdlist, 1, 1, PIPE))
			{
				if (i > 0)
					dup2(pipes[in], STDIN_FILENO);
				dup2(pipes[out], STDOUT_FILENO);
			}
			else
				dup2(pipes[in], STDIN_FILENO);
			close_pipes(pipes, j);
			get_bfunc(cmdlist->data, env_vars);
			close_pipes(pipes, j);
			exit(0);
		}
		cmdlist = update(cmdlist, i, &in, &out);
	}
	end_mult(pipes, j);
}
