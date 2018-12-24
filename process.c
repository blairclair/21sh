/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 13:07:26 by agrodzin          #+#    #+#             */
/*   Updated: 2018/09/20 13:54:23 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		get_process(char **args, char *arg, t_env_vars *env_vars)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(arg, args, env_vars->full_envs) == -1)
		{
			ft_printf("permission denied: please try agains %s %s\n",
			arg, strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		ft_printf("error forking\n");
		exit(EXIT_FAILURE);
	}
	waitpid(-1, 0, 0);
	return (1);
}

int		ft_exit(t_env_vars *env_vars)
{
	char	buf2[1024];
	char	*ap;

	ap = buf2;
	free_envs(env_vars);
	tcsetattr(0, TCSANOW, &g_termstuff.oldterm);
	ft_printf("\nprocess completed\n");
	exit(0);
}

void	print_two_rows(void)
{
	int	i;
	int	j;

	j = 0;
	ft_printf("%s", BLUE);
	while (j < 2)
	{
		i = 0;
		while (i < tgetnum("co"))
		{
			ft_printf("%c", '*');
			i++;
		}
		j++;
	}
}

void	get_user(void)
{
	print_two_rows();
	ft_printf("\n%sWelcome %s! To the greatest shell on earth!\n%s", RED,
	getenv("USER"), BLUE);
	print_two_rows();
	ft_printf("%s", BLACK);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		ft_strdel(&args[i]);
		i++;
	}
}
