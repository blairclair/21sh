/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 10:27:44 by agrodzin          #+#    #+#             */
/*   Updated: 2018/09/20 13:53:09 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

int		how_long(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

void	inner_loop(t_env_vars *env_vars, int i, int j, int k)
{
	while (env_vars->full_envs[k][i] != '=')
	{
		env_vars->env_names[env_vars->num_envs][i] =
			env_vars->full_envs[k][i];
		i++;
	}
	env_vars->env_names[env_vars->num_envs][i] = '\0';
	i++;
	while (env_vars->full_envs[k][i])
	{
		env_vars->env_values[env_vars->num_envs][j] =
			env_vars->full_envs[k][i];
		i++;
		j++;
	}
	env_vars->env_values[env_vars->num_envs][j] = '\0';
}

int		env_malloc_size(char **str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str[0]);
	while (str[i])
	{
		if ((int)ft_strlen(str[i]) > len)
			len = ft_strlen(str[i]);
		i++;
	}
	return ((i * len) + 2);
}

void	assign_env_names(t_env_vars *env_vars)
{
	int	i;
	int	j;
	int	k;

	k = 0;
	i = 0;
	j = 0;
	env_vars->env_names = ft_memalloc(env_malloc_size(env_vars->full_envs));
	env_vars->env_values = ft_memalloc(env_malloc_size(env_vars->full_envs));
	env_vars->num_envs = 0;
	while (env_vars->full_envs[k])
	{
		i = 0;
		j = 0;
		env_vars->env_names[env_vars->num_envs] =
		ft_memalloc(ft_strlen(env_vars->full_envs[env_vars->num_envs]) + 1);
		env_vars->env_values[env_vars->num_envs] =
		ft_memalloc(ft_strlen(env_vars->full_envs[env_vars->num_envs]) + 1);
		inner_loop(env_vars, i, j, k);
		env_vars->num_envs++;
		k++;
	}
}

int		ft_env(t_env_vars *env_vars)
{
	int	i;

	i = 0;
	while (i < env_vars->num_envs)
	{
		ft_printf("%s\n", env_vars->full_envs[i]);
		i++;
	}
	return (1);
}
