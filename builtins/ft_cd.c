/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 09:47:11 by agrodzin          #+#    #+#             */
/*   Updated: 2018/09/20 13:52:20 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

void	unset_pwd(char *pwd, t_env_vars *env_vars)
{
	int	i;

	i = 0;
	while (env_vars->env_names[i])
	{
		if (!ft_strcmp(env_vars->env_names[i], pwd))
		{
			free(env_vars->env_names[i]);
			free(env_vars->env_values[i]);
			free(env_vars->full_envs[i]);
			env_vars->env_names[i] = NULL;
			env_vars->env_values[i] = NULL;
			env_vars->full_envs[i] = NULL;
			break ;
		}
		i++;
	}
	resort_env(env_vars, i);
	env_vars->num_envs--;
}

void	change_pwd(char *mypwd, t_env_vars *env_vars)
{
	static int j = 0;

	unset_pwd("PWD", env_vars);
	reset_pwd(env_vars);
	if (j > 0)
	{
		unset_pwd("OLDPWD", env_vars);
		reset_old_pwd(env_vars);
	}
	free_cd(mypwd, env_vars);
	j++;
}

char	*assign_old_pwd(t_env_vars *env_vars)
{
	char	*mypwd;

	mypwd = ft_memalloc(140);
	getcwd(mypwd, 140);
	env_vars->oldpwd = ft_memalloc(100);
	if (mypwd != NULL)
		ft_strcpy(env_vars->oldpwd, mypwd);
	else
		ft_strcpy(env_vars->oldpwd, "Users/ariellagrodzinsky/21sh");
	return (mypwd);
}

int		ft_cd(char **args, t_env_vars *env_vars)
{
	int			i;
	struct stat	statcheck;
	char		*mypwd;

	i = get_num_args_minishell(args);
	mypwd = assign_old_pwd(env_vars);
	stat(args[1], &statcheck);
	if (i == 1)
		chdir(getenv("HOME"));
	else if (!ft_strcmp(args[1], "-"))
		last_cd(env_vars);
	else if (!ft_strcmp(args[1], "~") || args[1][0] == '~')
		tilda_cd(args, env_vars);
	else if (!S_ISDIR(statcheck.st_mode))
	{
		free(mypwd);
		free(env_vars->oldpwd);
		ft_printf("cd: not a directory %s\n", args[1]);
		return (1);
	}
	else
		chdir(args[1]);
	change_pwd(mypwd, env_vars);
	return (1);
}
