/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 10:58:41 by agrodzin          #+#    #+#             */
/*   Updated: 2018/09/20 13:52:33 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

int		get_num_par(char **args)
{
	int	num_par;
	int	i;
	int	j;

	i = 1;
	j = 0;
	num_par = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (args[i][j] == '"')
				num_par++;
			j++;
		}
		i++;
	}
	return (num_par);
}

char	*quote_is_closed(char *line, int fd, int quote_num, char *buf)
{
	char	fn[13];

	ft_strcpy(fn, "/tmp/.echpar");
	if (line[ft_strlen(line) - 1] == '"' && quote_num == 2)
	{
		line[ft_strlen(line) - 1] = '\0';
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
	}
	close(fd);
	fd = open(fn, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR);
	ft_printf("\n");
	read(fd, buf, 200);
	close(fd);
	free(line);
	return (buf);
}

void	echo_choices(char **args, int i)
{
	if (args[i][0] == '"')
	{
		if (args[i][ft_strlen(args[i]) - 1] == '"')
			args[i][ft_strlen(args[i]) - 1] = '\0';
		ft_printf("%s", args[i] + 1);
	}
	else if (args[i][ft_strlen(args[i]) - 1] == '"')
	{
		args[i][ft_strlen(args[i]) - 1] = '\0';
		ft_printf("%s", args[i]);
	}
	else
		ft_printf("%s", args[i]);
	if (args[i + 1] != NULL)
		ft_printf(" ");
}

int		ft_echo(char **args, t_env_vars *env_vars)
{
	int	i;

	i = 1;
	get_new_term();
	if (get_num_args_minishell(args) == 1)
		ft_printf("\n");
	else
	{
		while (args[i])
		{
			if (args[i][0] == '$')
				ft_printf("%s", get_val(args[i] + 1, env_vars));
			else
				echo_choices(args, i);
			i++;
		}
		ft_printf("\n");
	}
	get_first_term();
	return (1);
}
