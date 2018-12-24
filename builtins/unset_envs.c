/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_envs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 16:40:40 by agrodzin          #+#    #+#             */
/*   Updated: 2018/07/30 11:12:45 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

int		is_env(t_env_vars *env_vars, char *arg)
{
	int i;

	i = 0;
	while (env_vars->env_names[i])
	{
		if (!ft_strcmp(env_vars->env_names[i], arg))
			return (1);
		i++;
	}
	return (0);
}

int		resort_env(t_env_vars *env_vars, int i)
{
	while (i < env_vars->num_envs)
	{
		env_vars->env_names[i] = env_vars->env_names[i + 1];
		env_vars->env_values[i] = env_vars->env_values[i + 1];
		env_vars->full_envs[i] = env_vars->full_envs[i + 1];
		i++;
	}
	env_vars->full_envs[i] = NULL;
	return (1);
}

void	free_current_envs(t_env_vars *env_vars, int i)
{
	free(env_vars->env_names[i]);
	free(env_vars->env_values[i]);
	free(env_vars->full_envs[i]);
	env_vars->env_names[i] = NULL;
	env_vars->env_values[i] = NULL;
	env_vars->full_envs[i] = NULL;
}

int		ft_unset_env(char **arg, t_env_vars *env_vars)
{
	int i;

	i = 0;
	if (get_num_args_minishell(arg) <= 1)
	{
		ft_printf("please enter a value to unset\n");
		return (1);
	}
	if (!is_env(env_vars, arg[1]))
	{
		ft_printf("variable does not exist\n");
		return (1);
	}
	while (env_vars->env_names[i])
	{
		if (!ft_strcmp(env_vars->env_names[i], arg[1]))
		{
			free_current_envs(env_vars, i);
			break ;
		}
		i++;
	}
	env_vars->num_envs--;
	resort_env(env_vars, i);
	return (1);
}
