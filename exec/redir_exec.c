/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 21:07:26 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/25 21:07:27 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

t_execute	*fd_agg_check(t_execute *cmdlist, t_env_vars *env_vars)
{
	if (clist(cmdlist, 1, 2, NUM) && clist(cmdlist, 1, 3, PIPE))
	{
		redir_ag_pipe(cmdlist, env_vars, ft_atoi(cmdlist->prev->data[0]),
		ft_atoi(cmdlist->next->next->data[0]));
	}
	else if (clist(cmdlist, 1, 2, MINUS))
	{
		redir_ag_right(cmdlist, env_vars, ft_atoi(cmdlist->prev->data[0]), 300);
		while (cmdlist && cmdlist->type != MINUS)
			cmdlist = cmdlist->next;
	}
	else if (clist(cmdlist, 1, 3, NUM))
	{
		redir_ag_right(cmdlist, env_vars, ft_atoi(cmdlist->prev->data[0]),
		ft_atoi(cmdlist->next->next->next->data[0]));
		while (cmdlist && cmdlist->type != NUM)
			cmdlist = cmdlist->next;
	}
	return (cmdlist);
}

t_execute	*redir_right_exec(t_execute *cmdlist, t_env_vars *env_vars)
{
	if (clist(cmdlist, 0, 1, REGCMD) && clist(cmdlist, 1, 1, UNKNOWN))
	{
		if (cmdlist->prev->prev == NULL && cmdlist->next->next == NULL)
			redir_right(cmdlist, env_vars);
		else if (cmdlist->prev->prev == NULL && clist(cmdlist, 1, 2, SEMICOLON))
			redir_right(cmdlist, env_vars);
		else if (cmdlist->next->next == NULL && clist(cmdlist, 0, 2, SEMICOLON))
			redir_right(cmdlist, env_vars);
		else if (clist(cmdlist, 0, 2, SEMICOLON) &&
		clist(cmdlist, 1, 2, SEMICOLON))
			redir_right(cmdlist, env_vars);
	}
	else if (clist(cmdlist, 0, 1, NUM) && clist(cmdlist, 1, 1, AND))
		cmdlist = fd_agg_check(cmdlist, env_vars);
	return (cmdlist);
}

t_execute	*redir_left_exec(t_execute *cmdlist, t_env_vars *env_vars)
{
	if (clist(cmdlist, 0, 1, REGCMD) && clist(cmdlist, 1, 1, UNKNOWN))
	{
		if (cmdlist->prev->prev == NULL && cmdlist->next->next == NULL)
			redir_left(cmdlist, env_vars);
		else if (cmdlist->prev->prev == NULL && clist(cmdlist, 1, 2, SEMICOLON))
			redir_left(cmdlist, env_vars);
		else if (cmdlist->next->next == NULL && clist(cmdlist, 0, 2, SEMICOLON))
			redir_left(cmdlist, env_vars);
		else if (clist(cmdlist, 0, 2, SEMICOLON) &&
		clist(cmdlist, 1, 2, SEMICOLON))
			redir_left(cmdlist, env_vars);
		else if (cmdlist->prev->prev == NULL && (clist(cmdlist, 1, 2,
		REDIR1RIGHT) || clist(cmdlist, 1, 2, REDIR2RIGHT)))
			left_to_right(cmdlist, env_vars);
		else if (clist(cmdlist, 0, 2, SEMICOLON) && (clist(cmdlist, 1, 2,
		REDIR1RIGHT) || clist(cmdlist, 1, 2, REDIR2RIGHT)))
			left_to_right(cmdlist, env_vars);
	}
	return (cmdlist);
}

t_execute	*redir_two_left_exec_two(t_execute *cmdlist, t_env_vars *env_vars)
{
	if ((clist(cmdlist, 1, 4, REDIR1RIGHT) || clist(cmdlist, 1, 4,
	REDIR2RIGHT)) && clist(cmdlist, 1, 2, PIPE))
	{
		heredoc_to_pipe_to_redir(cmdlist, env_vars);
		while (cmdlist && cmdlist->type != REDIR1RIGHT &&
		cmdlist->type != REDIR2RIGHT)
			cmdlist = cmdlist->next;
	}
	else if (clist(cmdlist, 1, 2, PIPE))
	{
		piped_args_heredoc(cmdlist, env_vars);
		cmdlist = cmdlist->next->next->next;
	}
	return (cmdlist);
}

t_execute	*redir_two_left_exec(t_execute *cmdlist, t_env_vars *env_vars)
{
	if (clist(cmdlist, 0, 1, REGCMD) && clist(cmdlist, 1, 1, UNKNOWN))
	{
		if (cmdlist->prev->prev == NULL && cmdlist->next->next == NULL)
			redirtwo_left(cmdlist, env_vars);
		else if (clist(cmdlist, 0, 2, SEMICOLON) &&
		clist(cmdlist, 1, 2, SEMICOLON))
			redirtwo_left(cmdlist, env_vars);
		else if (clist(cmdlist, 0, 2, SEMICOLON) &&
		cmdlist->next->next == NULL)
			redirtwo_left(cmdlist, env_vars);
		else if (clist(cmdlist, 1, 2, SEMICOLON) &&
		cmdlist->prev->prev == NULL)
			redirtwo_left(cmdlist, env_vars);
		else if (clist(cmdlist, 1, 2, REDIR1RIGHT) ||
		clist(cmdlist, 1, 2, REDIR2RIGHT))
		{
			doub_left_to_right(cmdlist, env_vars);
			while (cmdlist && cmdlist->type != REDIR1RIGHT &&
			cmdlist->type != REDIR2RIGHT)
				cmdlist = cmdlist->next;
		}
		else
			cmdlist = redir_two_left_exec_two(cmdlist, env_vars);
	}
	return (cmdlist);
}
