/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execstuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 12:40:59 by agrodzin          #+#    #+#             */
/*   Updated: 2018/09/20 13:51:53 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

t_execute	*move_cmd_to(t_execute *cmdlist, t_tok_type syntype, int check)
{
	if (check == 1)
	{
		while (cmdlist)
		{
			if (cmdlist->type == syntype)
				break ;
			cmdlist = cmdlist->next;
		}
	}
	else
	{
		while (cmdlist && cmdlist->type == syntype)
		{
			if (cmdlist->next == NULL)
				break ;
			cmdlist = cmdlist->next;
		}
	}
	return (cmdlist);
}

int			is_pipe_to_redir(t_execute *cmdlist)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (cmdlist != NULL && (cmdlist->type == PIPE ||
	cmdlist->type == REDIR1RIGHT || cmdlist->type == REDIR2RIGHT))
	{
		if (cmdlist->type == REDIR1RIGHT || cmdlist->type == REDIR2RIGHT)
			num++;
		i++;
		cmdlist = cmdlist->next->next;
	}
	while (i > 0 && cmdlist != NULL)
	{
		cmdlist = cmdlist->prev->prev;
		i--;
	}
	return (num);
}

t_execute	*cmd_exec(t_execute *cmdlist, t_env_vars *env_vars)
{
	if (cmdlist->prev == NULL && cmdlist->next == NULL)
		get_bfunc(cmdlist->data, env_vars);
	else if (cmdlist->prev == NULL && clist(cmdlist, 1, 1, SEMICOLON))
		get_bfunc(cmdlist->data, env_vars);
	else if (cmdlist->next == NULL && clist(cmdlist, 0, 1, SEMICOLON))
		get_bfunc(cmdlist->data, env_vars);
	else if (clist(cmdlist, 0, 1, SEMICOLON) &&
	clist(cmdlist, 1, 1, SEMICOLON))
		get_bfunc(cmdlist->data, env_vars);
	return (cmdlist);
}

t_execute	*call_list_functions(t_execute *cmdlist, t_env_vars *env_vars)
{
	if (!bad_syntax(cmdlist) || !bad_syntax_two(cmdlist))
		ft_printf("bad syntax\n");
	else if (cmdlist->type == PIPE || cmdlist->type == REGCMD)
		cmdlist = (cmdlist->type == PIPE) ? pipe_exec(cmdlist, env_vars)
		: cmd_exec(cmdlist, env_vars);
	else if (cmdlist->type == REDIR1RIGHT || cmdlist->type == REDIR2RIGHT)
		cmdlist = redir_right_exec(cmdlist, env_vars);
	else if (cmdlist->type == REDIR1LEFT || cmdlist->type == REDIR2LEFT)
		cmdlist = (cmdlist->type == REDIR1LEFT) ? redir_left_exec(cmdlist,
		env_vars) : redir_two_left_exec(cmdlist, env_vars);
	else if (cmdlist->type == UNKNOWN)
		cmdlist = unknown_exec(cmdlist);
	return (cmdlist);
}

int			use_list(t_execute *cmdlist, t_env_vars *env_vars)
{
	t_execute	*head;
	int			tmpin;
	int			tmpout;

	tmpin = dup(0);
	tmpout = dup(1);
	head = cmdlist;
	while (cmdlist != NULL)
	{
		cmdlist = call_list_functions(cmdlist, env_vars);
		cmdlist = cmdlist->next;
		restore_fd(tmpin, tmpout);
	}
	close_in_out_fd(tmpin, tmpout);
	free_everything(head);
	return (1);
}
