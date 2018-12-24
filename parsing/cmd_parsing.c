/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:27:04 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/23 12:27:18 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

int		cmd_parsing(char **arg, char *str, t_execute **cmdlist, int i)
{
	struct stat statcheck;

	lstat(arg[0], &statcheck);
	if (is_builtin(arg[0]))
	{
		i = add_reg_cmd(i, arg, &*cmdlist, str);
		return (i);
	}
	else if (statcheck.st_mode & S_IXUSR && ft_strcmp(arg[0], "")
	&& access(arg[0], X_OK) == 0)
	{
		i = add_reg_cmd(i, arg, &*cmdlist, str);
		return (i);
	}
	return (-1);
}

int		cmd_parsing_two(char **arg, char *str,
t_execute **cmdlist, int i)
{
	int	num;

	if (str[i + 1] == '\0' && !ft_isdelim(str[i]))
		arg[0][ft_strlen(arg[0])] = str[i];
	if ((num = cmd_parsing(arg, str, &*cmdlist, i)) > 0)
	{
		i = num;
		return (i);
	}
	return (i);
}

int		add_reg_cmd(int i, char **arg, t_execute **cmdlist, char *str)
{
	i = find_flag(arg, str, i);
	add_to_end(&*cmdlist, 1, arg, REGCMD);
	clear_two_d(arg);
	return (i);
}
