/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 17:39:34 by agrodzin          #+#    #+#             */
/*   Updated: 2018/09/20 13:51:26 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"

int		get_bfunc(char **args, t_env_vars *env_vars)
{
	if (!ft_strcmp(args[0], "cd"))
		ft_cd(args, env_vars);
	else if (!ft_strcmp(args[0], "echo"))
		ft_echo(args, env_vars);
	else if (!ft_strcmp(args[0], "exit"))
		return (ft_exit(env_vars));
	else if (!ft_strcmp(args[0], "env"))
		ft_env(env_vars);
	else if (!ft_strcmp(args[0], "setenv"))
	{
		if (get_num_args_minishell(args) <= 1)
			ft_printf("please enter a value to set\n");
		else
			ft_setenv(args, env_vars);
	}
	else if (!ft_strcmp(args[0], "unsetenv"))
		ft_unset_env(args, env_vars);
	else if (check_path(args, env_vars) == -1)
	{
		if (access(args[0], F_OK) != -1)
			get_process(args, args[0], env_vars);
		else
			ft_printf("command not found: %s\n", args[0]);
	}
	return (1);
}

void	define_line(void)
{
	if (!g_termstuff.origline)
		g_termstuff.origline = ft_memalloc(2);
	else
		ft_bzero(g_termstuff.origline, ft_strlen(g_termstuff.origline));
}

char	*get_new_line(t_execute *cmdlist, t_env_vars *env_vars)
{
	unsigned long	d;

	define_line();
	while (1)
	{
		d = 0;
		read(0, &d, 6);
		if (d == ENTER)
		{
			while (g_termstuff.row_pos < g_termstuff.rowlen)
			{
				tputs(tgetstr("do", NULL), 0, ft_charput);
				g_termstuff.row_pos++;
			}
			reset_highlight(g_termstuff.origline);
			save_history(g_termstuff.origline);
			check_quotes();
			g_termstuff.changed_len = 0;
			ft_printf("\n");
			update_values();
			return (g_termstuff.origline);
		}
		else
			line_ed_one(d, env_vars, cmdlist);
	}
}

void	minloop(void)
{
	t_execute	cmdlist;
	char		*line;
	int			status;
	char		*templine;
	t_env_vars	env_vars;

	initialize_envs(&env_vars);
	status = 1;
	get_user();
	signal(SIGINT, sighandlec);
	signal(SIGWINCH, sighandlewindow);
	while (status)
	{
		if (!ft_strcmp(g_history[g_termstuff.historypos - 1], "cat"))
			ft_printf("\n");
		ft_printf("What say you-> ");
		get_new_term();
		get_new_line(&cmdlist, &env_vars);
		templine = g_termstuff.origline;
		line = ft_strtrim(g_termstuff.origline);
		get_first_term();
		if (!islinejustspacetab(line))
			status = create_list(line, &env_vars, &cmdlist);
		free(line);
	}
}

int		main(void)
{
	char					*name;
	char					buf[1024];

	g_termstuff.rowlen = 1;
	tgetent(buf, name);
	set_term_environ();
	minloop();
	return (0);
}
