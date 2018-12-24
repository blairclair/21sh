/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:48:16 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/23 12:48:31 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

int		fd_agg_parsing(char **arg, char *str, t_execute **cmdlist, int i)
{
	clear_two_d(arg);
	arg[0][0] = str[i];
	add_to_end(&*cmdlist, 1, arg, NUM);
	clear_two_d(arg);
	if (str[i + 1] && str[i + 1] == '-')
	{
		add_to_end(&*cmdlist, 1, arg, MINUS);
		i++;
	}
	return (i);
}

int		redir_right_parsing(char **arg, char *str, t_execute **cmdlist, int i)
{
	if (str[i] && str[i + 1] == '>')
	{
		add_to_end(&*cmdlist, 1, arg, REDIR2RIGHT);
		i++;
	}
	else
		add_to_end(&*cmdlist, 1, arg, REDIR1RIGHT);
	return (i);
}

int		redir_left_parsing(char **arg, char *str, t_execute **cmdlist, int i)
{
	if (str[i] && str[i + 1] == '<')
	{
		add_to_end(&*cmdlist, 1, arg, REDIR2LEFT);
		i++;
	}
	else
		add_to_end(&*cmdlist, 1, arg, REDIR1LEFT);
	return (i);
}

int		redir_parsing(char **arg, char *str, t_execute **cmdlist, int i)
{
	if (str[i] == '<')
	{
		i = redir_left_parsing(arg, str, &*cmdlist, i);
		return (i);
	}
	else if (str[i] == '>')
	{
		i = redir_right_parsing(arg, str, &*cmdlist, i);
		return (i);
	}
	else if (ft_isdigit(str[i]) && ((str[i + 1] != '\0'
	&& str[i + 1] == '>') || (str[i - 1] != '\0' && str[i - 1] == '&')))
	{
		i = fd_agg_parsing(arg, str, &*cmdlist, i);
		return (i);
	}
	return (-1);
}
