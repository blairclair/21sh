/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 21:09:35 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/25 21:09:37 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

int			is_pipe_mult_to_redir(t_execute *cmdlist)
{
	t_execute	*tmplist;

	tmplist = cmdlist;
	if (clist(tmplist, 1, 2, PIPE))
	{
		while (tmplist != NULL)
		{
			if (tmplist->type != PIPE && tmplist->type != REDIR1RIGHT &&
			tmplist->type != REDIR2RIGHT)
				return (0);
			if (tmplist->type == REDIR1RIGHT || tmplist->type == REDIR2RIGHT)
				return (1);
			if (tmplist->next && tmplist->next->next)
				tmplist = tmplist->next->next;
			else
				return (0);
		}
	}
	return (0);
}

t_execute	*pipe_to_redir_exec(t_execute *cmdlist)
{
	pipe_to_redir(cmdlist, 1, get_num_pipes(cmdlist) + 1, 0);
	while (cmdlist && cmdlist->type == PIPE)
	{
		if (cmdlist->next && cmdlist->next->next)
			cmdlist = cmdlist->next->next;
		else
			cmdlist = cmdlist->next;
	}
	return (cmdlist);
}

t_execute	*pipe_mult_exec(t_execute *cmdlist, t_env_vars *env_vars)
{
	pipe_mult(cmdlist, env_vars, 0, 1);
	while (cmdlist && cmdlist->type == PIPE)
	{
		if (cmdlist->next && cmdlist->next->next)
			cmdlist = cmdlist->next->next;
		else
			cmdlist = cmdlist->next;
	}
	return (cmdlist);
}

t_execute	*pipe_exec(t_execute *cmdlist, t_env_vars *env_vars)
{
	if (clist(cmdlist, 0, 1, UNKNOWN) && clist(cmdlist, 1, 1, UNKNOWN))
		ft_printf("command not found: %s\n", cmdlist->prev->data[0]);
	else if (clist(cmdlist, 0, 1, REGCMD) && clist(cmdlist, 1, 1, REGCMD))
	{
		if (clist(cmdlist, 1, 2, REDIR1RIGHT) ||
		clist(cmdlist, 1, 2, REDIR2RIGHT) || is_pipe_mult_to_redir(cmdlist))
			cmdlist = pipe_to_redir_exec(cmdlist);
		else if (clist(cmdlist, 1, 2, PIPE))
			cmdlist = pipe_mult_exec(cmdlist, env_vars);
		else if (cmdlist->prev->prev == NULL && cmdlist->next->next == NULL)
			piped_args(env_vars, cmdlist->prev->data, cmdlist->next->data, 1);
		else if (clist(cmdlist, 0, 2, SEMICOLON) &&
		clist(cmdlist, 1, 2, SEMICOLON))
			piped_args(env_vars, cmdlist->prev->data, cmdlist->next->data, 1);
		else if (clist(cmdlist, 0, 2, SEMICOLON) &&
		cmdlist->next->next == NULL)
			piped_args(env_vars, cmdlist->prev->data, cmdlist->next->data, 1);
		else if (clist(cmdlist, 1, 2, SEMICOLON) && cmdlist->prev->prev == NULL)
			piped_args(env_vars, cmdlist->prev->data, cmdlist->next->data, 1);
	}
	return (cmdlist);
}
