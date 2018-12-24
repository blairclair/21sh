/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/18 14:17:30 by agrodzin          #+#    #+#             */
/*   Updated: 2018/09/20 13:54:04 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

int		token_parsing_one(char *str, int i, t_execute **cmdlist, char **arg)
{
	if (str[i] && str[i] == ';')
		add_to_end(&*cmdlist, 1, arg, SEMICOLON);
	else if (str[i] && str[i] == '&')
	{
		add_to_end(&*cmdlist, 1, arg, AND);
		if (str[i + 1] && str[i + 1] == '-')
		{
			add_to_end(&*cmdlist, 1, arg, MINUS);
			i++;
		}
	}
	else if (str[i] && str[i] == '|')
		add_to_end(&*cmdlist, 1, arg, PIPE);
	else if (str[i] == '&')
		add_to_end(&*cmdlist, 1, arg, AND);
	if (str[i] == ';' || str[i] == '&' || str[i] == '|')
		return (i);
	return (-1);
}

int		parse_all_space(char **arg, t_execute **cmdlist, char *str, int i)
{
	free_two(arg, 1);
	add_to_end(&*cmdlist, 1, arg, UNKNOWN);
	clear_two_d(arg);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}

int		add_to_arg(char **arg, int i, int j, char *str)
{
	if (ft_isdelim(str[i]))
	{
		clear_two_d(arg);
		j = 0;
	}
	if (str[i] != ' ' && str[i] != '\t')
	{
		arg[0][j] = str[i];
		j++;
	}
	return (j);
}

int		get_num(char *str, int i, t_execute **cmdlist, char **arg)
{
	int	num;

	num = token_parsing_one(str, i, &*cmdlist, arg);
	if (num > -1)
	{
		i = num;
		return (i);
	}
	else if ((num = redir_parsing(arg, str, &*cmdlist, i)) > 0)
	{
		i = num;
		return (i);
	}
	return (-1);
}

int		create_list(char *str, t_env_vars *env_vars, t_execute *cmdlist)
{
	int			i;
	char		**arg;
	int			j;
	int			num;

	i = define_values_create_list(str, &arg, &j, &cmdlist);
	if ((num = single_letter(str, arg, &cmdlist)) > 0)
		return (use_list(cmdlist, env_vars));
	while (str[++i])
	{
		if (ft_isspacetab(str[i]) || ft_isdelim(str[i]) || str[i + 1] == '\0')
		{
			i = cmd_parsing_two(arg, str, &cmdlist, i);
			if (!ft_isdigit(str[i]) && ispath(arg[0], env_vars))
				i = add_reg_cmd(i, arg, &cmdlist, str);
			i = ft_isallspace(arg, &cmdlist, str, i);
			j = 0;
		}
		if ((num = get_num(str, i, &cmdlist, arg)) > 0)
			i = num;
		else
			j = add_to_arg(arg, i, j, str);
	}
	free_two_d(arg);
	return (use_list(cmdlist, env_vars));
}
