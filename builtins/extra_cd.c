/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 13:03:31 by agrodzin          #+#    #+#             */
/*   Updated: 2018/09/20 13:52:06 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

int		ft_cd_home(t_env_vars *env_vars)
{
	int	i;

	i = 0;
	while (env_vars->env_names[i])
	{
		if (!ft_strcmp(env_vars->env_names[i], "HOME"))
			break ;
		i++;
	}
	chdir(env_vars->env_values[i]);
	return (1);
}

int		tilda_home(char **args, char *tmpcwd, t_env_vars *env_vars)
{
	if (ft_strlen(args[1]) == 1 && get_num_args_minishell(args) == 2)
	{
		chdir(tmpcwd);
		ft_printf("%s\n", tmpcwd);
	}
	else if (get_num_args_minishell(args) > 2)
	{
		ft_printf("cd: not a directory %s%s\n",
				args[2], get_val("PWD", env_vars));
	}
	else
		return (0);
	return (1);
}

int		tilda_other(char **args, char *tmparg, char *tmpcwd)
{
	struct stat	statcheck;

	if (get_num_args_minishell(args) == 2)
	{
		ft_strcat(tmpcwd, tmparg);
		lstat(tmpcwd, &statcheck);
		if (!S_ISDIR(statcheck.st_mode))
			ft_printf("cd: not a directory %s\n", tmparg);
		else
		{
			chdir(tmpcwd);
			ft_bzero(tmparg, ft_strlen(tmparg));
			getcwd(tmparg, 140);
			ft_printf("%s\n", tmparg);
		}
	}
	return (1);
}

int		tilda_cd(char **args, t_env_vars *env_vars)
{
	char		tmpcwd[140];
	char		tmparg[250];
	int			i;
	int			j;

	j = 0;
	i = 1;
	ft_strcpy(tmpcwd, getenv("HOME"));
	while (args[1][i])
	{
		if (args[1][i] == '\\' && (int)ft_strlen(args[1]) == i + 1)
			break ;
		tmparg[j] = args[1][i];
		i++;
		j++;
	}
	tmparg[j] = '\0';
	if (!tilda_home(args, tmpcwd, env_vars))
	{
		tilda_other(args, tmparg, tmpcwd);
	}
	return (1);
}

int		last_cd(t_env_vars *env_vars)
{
	if (get_val("OLDPWD", env_vars) != NULL)
	{
		ft_printf("%s\n", get_val("OLDPWD", env_vars));
		chdir(get_val("OLDPWD", env_vars));
		return (1);
	}
	else
		ft_printf("%s\n", get_val("PWD", env_vars));
	return (0);
}
