/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 11:11:44 by agrodzin          #+#    #+#             */
/*   Updated: 2018/07/30 11:12:32 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

int		get_num_args_minishell(char **args)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	free_same_env(char *tmpname, t_env_vars *env_vars)
{
	ft_printf("%s already exists\n", tmpname);
	free(env_vars->env_names[env_vars->num_envs]);
	free(env_vars->env_values[env_vars->num_envs]);
	free(env_vars->full_envs[env_vars->num_envs]);
	env_vars->env_names[env_vars->num_envs] = NULL;
	env_vars->env_values[env_vars->num_envs] = NULL;
	env_vars->full_envs[env_vars->num_envs] = NULL;
	free(tmpname);
}

int		get_new_env(char **args, t_env_vars *env_vars, int i, int j)
{
	char	*tmpname;

	tmpname = ft_memalloc(ft_strlen(args[1]) + 2);
	env_vars->full_envs[env_vars->num_envs] = ft_strdup(args[1]);
	while (args[1][i] != '=')
	{
		tmpname[i] = args[1][i];
		i++;
	}
	if (is_env(env_vars, tmpname))
	{
		free_same_env(tmpname, env_vars);
		return (0);
	}
	free(env_vars->env_names[env_vars->num_envs]);
	env_vars->env_names[env_vars->num_envs] = tmpname;
	i++;
	while (args[1][i])
	{
		env_vars->env_values[env_vars->num_envs][j] = args[1][i];
		i++;
		j++;
	}
	env_vars->num_envs++;
	return (1);
}

int		ft_setenv(char **args, t_env_vars *env_vars)
{
	if (!how_many2d(args, '='))
	{
		ft_printf("bad setenv input\n");
		return (1);
	}
	env_vars->env_names[env_vars->num_envs] =
	ft_memalloc(ft_strlen(args[1]) + 2);
	env_vars->env_values[env_vars->num_envs] =
	ft_memalloc(ft_strlen(args[1]) + 2);
	if (get_num_args_minishell(args) == 2)
	{
		if (!get_new_env(args, env_vars, 0, 0))
			return (1);
	}
	else
	{
		free(env_vars->env_names[env_vars->num_envs]);
		free(env_vars->env_values[env_vars->num_envs]);
		ft_printf("bad setenv input\n");
	}
	return (1);
}
