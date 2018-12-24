/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 21:32:47 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/25 21:32:48 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void	free_everything(t_execute *cmdlist)
{
	t_execute	*tmp;

	while (cmdlist != NULL)
	{
		tmp = cmdlist->next;
		free_two_d(cmdlist->data);
		free(cmdlist);
		cmdlist = tmp;
	}
}

char	*ft_21_free_first_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		i;

	i = 0;
	s3 = (char*)ft_memalloc(ft_strlen(s1) + ft_strlen(s2) +
	(tgetnum("co") * tgetnum("li")));
	if (s3 == NULL)
		return (NULL);
	ft_strcpy(s3, s1);
	ft_strcat(s3, s2);
	while (s3[i])
		i++;
	s3[i] = '\0';
	free(s1);
	free(s2);
	return (s3);
}

void	free_envs(t_env_vars *env_vars)
{
	int	i;

	i = 0;
	while (env_vars->full_envs[i])
	{
		free(env_vars->full_envs[i]);
		free(env_vars->env_names[i]);
		free(env_vars->env_values[i]);
		i++;
	}
	free(env_vars->env_names);
	free(env_vars->env_values);
	free(env_vars->full_envs);
}

void	free_cd(char *mypwd, t_env_vars *env_vars)
{
	free(env_vars->env_names[env_vars->num_envs]);
	free(env_vars->env_values[env_vars->num_envs]);
	free(env_vars->full_envs[env_vars->num_envs]);
	free(mypwd);
	free(env_vars->oldpwd);
}
