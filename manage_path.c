/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 09:31:20 by agrodzin          #+#    #+#             */
/*   Updated: 2018/09/20 13:53:46 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

char	*get_temp(char *arg, char **p, int i)
{
	char	*temp;

	temp = ft_21_strjoin("", p[i]);
	ft_strcat(temp, "/");
	ft_strcat(temp, arg);
	return (temp);
}

int		ispath(char *arg, t_env_vars *env_vars)
{
	int			i;
	char		*value;
	char		**p;
	struct stat	statcheck;
	char		*temp;

	if (arg == NULL || !ft_strcmp(arg, "") ||
	(value = get_val("PATH", env_vars)) == NULL)
		return (0);
	p = ft_strsplit(value, ':');
	i = -1;
	while (p[++i])
	{
		temp = get_temp(arg, p, i);
		lstat(temp, &statcheck);
		if (statcheck.st_mode & S_IXUSR && access(temp, X_OK) == 0)
		{
			free_two_d(p);
			free(temp);
			return (1);
		}
		free(temp);
	}
	free_two_d(p);
	return (0);
}

char	*get_val(char *value, t_env_vars *env_vars)
{
	int	i;

	i = 0;
	while (env_vars->env_names[i])
	{
		if (!ft_strcmp(env_vars->env_names[i], value))
			return (env_vars->env_values[i]);
		i++;
	}
	return (NULL);
}

int		check_path(char **args, t_env_vars *env_vars)
{
	int		i;
	char	*value;
	char	**p;

	i = ft_strlen(args[0]);
	if ((value = get_val("PATH", env_vars)) == NULL)
		return (-1);
	p = ft_strsplit(value, ':');
	i = 0;
	while (p[i])
	{
		p[i] = ft_strcat(p[i], "/");
		p[i] = ft_strcat(p[i], args[0]);
		if (access(p[i], F_OK) > -1)
		{
			get_process(args, p[i], env_vars);
			free_two_d(p);
			return (1);
		}
		i++;
	}
	free_two_d(p);
	return (-1);
}
