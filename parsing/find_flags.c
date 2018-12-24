/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 11:22:55 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/25 21:46:55 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

int		ft_flag_two(char **arg, char *str, int *j, int *num)
{
	int	k;

	k = ft_strlen(arg[*num]);
	if (str[(*j) + 1] == '\0' && str[*j] != '\'')
	{
		arg[*(num)][k] = str[*(j)];
		(*num)++;
		return (0);
	}
	else if (str[(*j) + 1] != ' ' && str[(*j) + 1] != '\t' &&
			!ft_isdelim(str[*j]) && str[*j] != '\'')
	{
		arg[*num][k] = str[*j];
		(*num)++;
		return (0);
	}
	else
	{
		(*num)++;
		return (0);
	}
	return (1);
}

int		ft_flag_one(char **arg, char *str, int *num, int *j)
{
	while (str[*j] == ' ' || str[*j] == '\t')
		(*j)++;
	if (ft_isdigit(str[*j]) && ((str[(*j) + 1] != '\0'
					&& str[(*j) + 1] == '>') ||
				(str[(*j) - 1] != '\0' && str[(*j) - 1] == '&')))
	{
		(*num)++;
		(*j)--;
		return (-1);
	}
	if (!ft_isdelim(str[*j]) && str[(*j) + 1] != '\0')
	{
		(*num)++;
		if (!arg[*num])
			arg[*num] = ft_memalloc(ft_strlen(str));
		return (0);
	}
	return (1);
}

int		ft_flag_three(char *str, char **arg, int *num, int *j)
{
	int	check;
	int	k;

	k = ft_strlen(arg[*num]);
	if (ft_isdigit(str[*j]) && ((str[(*j) + 1] != '\0'
					&& str[(*j) + 1] == '>') ||
				(str[(*j) - 1] != '\0' && str[(*j) - 1] == '&')))
		return (-1);
	if (str[*j] == ' ' || str[*j] == '\t' || ft_isdelim(str[*j]) ||
			str[(*j) + 1] == '\0')
	{
		if ((check = ft_flag_one(arg, str, num, j)) == -1)
			return (-1);
		else if (check == 0)
			k = 0;
		else
		{
			if (ft_flag_two(arg, str, j, num) == 0)
				return (-1);
		}
	}
	return (k);
}

int		start_flag(char **arg, char *str, int *j, int i)
{
	free_two(arg, 1);
	while (str[*j] == ' ' || str[*j] == '\t')
		(*j)++;
	if (ft_isdelim(str[*j]) || ft_isdelim(str[(*j) + 1]) || str[i + 1] == '\0')
	{
		arg[1] = NULL;
		return (i);
	}
	if (!arg[1])
		arg[1] = ft_memalloc(ft_strlen(str) + 1);
	return (-1);
}

int		find_flag(char **arg, char *str, int i)
{
	int k;
	int j;
	int num;
	int	check;

	j = i;
	num = 1;
	k = -1;
	if (start_flag(arg, str, &j, i) > -1)
		return (i);
	while (str[j])
	{
		if ((check = ft_flag_three(str, arg, &num, &j)) == -1)
			break ;
		else if (check == 0)
			k = -1;
		if ((str[j] != ' ' || str[j] != '\t' ||
		!ft_isdelim(str[j]) || str[j + 1] != '\0') && str[j] != '\'')
		{
			arg[num][++k] = str[j];
		}
		j++;
	}
	arg[num] = NULL;
	return (j);
}
