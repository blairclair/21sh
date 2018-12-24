/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 14:11:58 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/23 14:12:09 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

int		ft_isallspace(char **arg, t_execute **cmdlist, char *str, int i)
{
	int	j;

	j = 0;
	if (arg[0] == NULL)
		return (1);
	while (arg[0][j])
	{
		if (arg[0][j] != ' ' || arg[0][j] != '\t')
		{
			free_two(arg, 1);
			add_to_end(&*cmdlist, 1, arg, UNKNOWN);
			clear_two_d(arg);
			while (str[i] == ' ' || str[i] == '\t')
				i++;
			return (i);
		}
		j++;
	}
	return (i);
}

int		single_letter(char *str, char **arg, t_execute **cmdlist)
{
	if (ft_strlen(str) == 1)
	{
		ft_strcpy(arg[0], str);
		arg[1] = NULL;
		add_to_end(&*cmdlist, 1, arg, UNKNOWN);
		free_two_d(arg);
		return (1);
	}
	return (-1);
}
