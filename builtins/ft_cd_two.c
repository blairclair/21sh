/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 21:30:03 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/25 21:30:04 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

void	reset_pwd(t_env_vars *env_vars)
{
	if (!env_vars->env_names[env_vars->num_envs])
	{
		env_vars->env_names[env_vars->num_envs] = ft_memalloc(5);
		ft_strcpy(env_vars->env_names[env_vars->num_envs], "PWD");
	}
	env_vars->env_values[env_vars->num_envs] = ft_memalloc(140);
	if (!env_vars->full_envs[env_vars->num_envs])
		env_vars->full_envs[env_vars->num_envs] = ft_memalloc(145);
	else
		ft_bzero(env_vars->full_envs[env_vars->num_envs],
		ft_strlen(env_vars->full_envs[env_vars->num_envs]));
	getcwd(env_vars->env_values[env_vars->num_envs], 70);
	ft_strcpy(env_vars->full_envs[env_vars->num_envs],
				env_vars->env_names[env_vars->num_envs]);
	ft_strcat(env_vars->full_envs[env_vars->num_envs], "=");
	ft_strcat(env_vars->full_envs[env_vars->num_envs],
				env_vars->env_values[env_vars->num_envs]);
	env_vars->num_envs++;
}

void	reset_old_pwd(t_env_vars *env_vars)
{
	if (!env_vars->env_names[env_vars->num_envs])
	{
		env_vars->env_names[env_vars->num_envs] = ft_memalloc(10);
		ft_strcpy(env_vars->env_names[env_vars->num_envs], "OLDPWD");
	}
	env_vars->env_values[env_vars->num_envs] = ft_memalloc(140);
	env_vars->full_envs[env_vars->num_envs] = ft_memalloc(150);
	ft_strcpy(env_vars->env_values[env_vars->num_envs], env_vars->oldpwd);
	ft_strcpy(env_vars->full_envs[env_vars->num_envs],
				env_vars->env_names[env_vars->num_envs]);
	ft_strcat(env_vars->full_envs[env_vars->num_envs], "=");
	ft_strcat(env_vars->full_envs[env_vars->num_envs],
				env_vars->env_values[env_vars->num_envs]);
	env_vars->num_envs++;
}
