/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 10:27:54 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/23 10:27:58 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

void		define_values_rep_line(int *j, int *i, char *str)
{
	int	col;

	*j = 0;
	*i = 1;
	g_termstuff.multine = 0;
	col = tgetnum("co");
	if (g_termstuff.changed_len > 0 && g_termstuff.changed_len < 20000)
	{
		g_termstuff.whole_line_len = ft_strlen(str);
		g_termstuff.row_pos = (g_termstuff.track / (col - 16)) + 1;
		g_termstuff.rowlen = (g_termstuff.whole_line_len / (col - 16)) + 1;
		g_termstuff.changed_len = 20000;
	}
	if (g_termstuff.collen > col)
	{
		g_termstuff.row_pos = (g_termstuff.track / (col - 16)) + 1;
		g_termstuff.rowlen = (g_termstuff.whole_line_len / (col - 16)) + 1;
		g_termstuff.collen = 0;
	}
	*i = 1;
}

void		initialize_envs(t_env_vars *env_vars)
{
	extern char	**environ;
	int			i;
	int			j;

	i = 0;
	j = 0;
	env_vars->full_envs = ft_memalloc(env_malloc_size(environ));
	while (environ[i])
	{
		env_vars->full_envs[j] = ft_strdup(environ[i]);
		j++;
		i++;
	}
	assign_env_names(env_vars);
}

void		define_values_history_rep_line(int col)
{
	if (g_termstuff.whole_line_len > (col - 16))
	{
		g_termstuff.rowlen = (g_termstuff.track / (col - 16)) + 1;
		g_termstuff.row_pos = (g_termstuff.track / (col - 16)) + 1;
	}
	else
	{
		g_termstuff.rowlen = 1;
		g_termstuff.row_pos = 1;
		g_termstuff.collen = g_termstuff.whole_line_len + 15;
	}
	g_termstuff.multine = 0;
}

int			define_values_create_list(char *str, char ***arg,
int *j, t_execute **cmdlist)
{
	int	i;

	i = -1;
	(*j) = 0;
	*arg = ft_memalloc(ft_strlen(str) * ft_strlen(str) * sizeof(char *) + 1);
	*arg[0] = ft_memalloc(ft_strlen(str) + 2);
	(*cmdlist) = NULL;
	return (i);
}

t_execute	*define_first_vars(int *i, int *j, t_execute *cmdlist, int pipes[])
{
	*i = -1;
	*j = get_num_pipes(cmdlist);
	cmdlist = cmdlist->prev;
	pipe_pipes(pipes, *i, *j);
	return (cmdlist);
}
