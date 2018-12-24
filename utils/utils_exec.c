/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 20:47:34 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/25 20:47:36 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

t_execute	*unknown_exec(t_execute *cmdlist)
{
	if (cmdlist->prev == NULL && cmdlist->next == NULL)
		ft_printf("command not found: %s\n", cmdlist->data[0]);
	else if (cmdlist->prev == NULL && clist(cmdlist, 1, 1, SEMICOLON))
		ft_printf("command not found: %s\n", cmdlist->data[0]);
	else if (cmdlist->next == NULL && clist(cmdlist, 0, 1, SEMICOLON))
		ft_printf("command not found: %s\n", cmdlist->data[0]);
	else if (clist(cmdlist, 0, 1, SEMICOLON) && clist(cmdlist, 1, 1, SEMICOLON))
		ft_printf("command not found: %s\n", cmdlist->data[0]);
	else if (clist(cmdlist, 1, 1, UNKNOWN))
	{
		if (cmdlist->prev == NULL || clist(cmdlist, 0, 1, SEMICOLON))
		{
			ft_printf("command not found: %s\n", cmdlist->data[0]);
			move_cmd_to(cmdlist, UNKNOWN, 0);
		}
	}
	return (cmdlist);
}

int			bad_syntax_two(t_execute *cmdlist)
{
	if ((cmdlist->type == PIPE) && (clist(cmdlist, 0, 1, PIPE)
	|| clist(cmdlist, 1, 1, PIPE)))
		return (0);
	if ((cmdlist->type == REDIR1RIGHT || cmdlist->type == REDIR2RIGHT ||
	cmdlist->type == REDIR1LEFT || cmdlist->type == REDIR2LEFT) &&
	(clist(cmdlist, 0, 1, REDIR1RIGHT) || clist(cmdlist, 1, 1, REDIR1RIGHT)))
		return (0);
	if ((cmdlist->type == REDIR1RIGHT || cmdlist->type == REDIR2RIGHT ||
	cmdlist->type == REDIR1LEFT || cmdlist->type == REDIR2LEFT) &&
	(clist(cmdlist, 0, 1, REDIR2RIGHT) || clist(cmdlist, 1, 1, REDIR2RIGHT)))
		return (0);
	if ((cmdlist->type == REDIR1RIGHT || cmdlist->type == REDIR2RIGHT ||
	cmdlist->type == REDIR1LEFT || cmdlist->type == REDIR2LEFT) &&
	(clist(cmdlist, 0, 1, REDIR2LEFT) || clist(cmdlist, 1, 1, REDIR2LEFT)))
		return (0);
	if ((cmdlist->type == REDIR1RIGHT || cmdlist->type == REDIR2RIGHT ||
	cmdlist->type == REDIR1LEFT || cmdlist->type == REDIR2LEFT)
	&& (clist(cmdlist, 0, 1, REDIR1LEFT) || clist(cmdlist, 1, 1, REDIR1LEFT)))
		return (0);
	if ((cmdlist->type == REDIR1RIGHT || cmdlist->type == REDIR2RIGHT ||
	cmdlist->type == REDIR1LEFT || cmdlist->type == REDIR2LEFT) &&
	(clist(cmdlist, 0, 1, PIPE) || clist(cmdlist, 1, 1, REDIR2LEFT)))
		return (0);
	return (1);
}

int			bad_syntax(t_execute *cmdlist)
{
	if ((cmdlist->type == PIPE) && (clist(cmdlist, 0, 1, REDIR1RIGHT) ||
	clist(cmdlist, 1, 1, REDIR1RIGHT)))
		return (0);
	if ((cmdlist->type == PIPE) && (clist(cmdlist, 0, 1, REDIR2RIGHT) ||
	clist(cmdlist, 1, 1, REDIR2RIGHT)))
		return (0);
	if ((cmdlist->type == PIPE) && (clist(cmdlist, 0, 1, REDIR2LEFT) ||
	clist(cmdlist, 1, 1, REDIR2LEFT)))
		return (0);
	if ((cmdlist->type == PIPE) && (clist(cmdlist, 0, 1, REDIR1LEFT) ||
	clist(cmdlist, 1, 1, REDIR1LEFT)))
		return (0);
	return (1);
}
