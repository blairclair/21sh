/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 11:43:15 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/23 11:43:37 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

void	close_in_out_fd(int tmpin, int tmpout)
{
	close(tmpin);
	close(tmpout);
}

void	restore_fd(int tmpin, int tmpout)
{
	dup2(tmpout, STDOUT_FILENO);
	dup2(tmpin, STDIN_FILENO);
}

char	*get_fn_and_print_line(char *line, int fd)
{
	char	*fn;

	fn = ft_memalloc(50);
	ft_strcpy(fn, getenv("HOME"));
	ft_strcat(fn, "/");
	ft_strcat(fn, ".tmpheredoctmp");
	ft_putstr_fd(line, fd);
	ft_putchar_fd('\n', fd);
	close(fd);
	return (fn);
}

char	*ft_21_strjoin(char *s1, char *s2)
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
	return (s3);
}

int		clist(t_execute *cmdlist, int dir, int num, t_tok_type syntype)
{
	int	i;

	i = -1;
	while (++i < num)
	{
		if (dir == 0 && cmdlist->prev)
			cmdlist = cmdlist->prev;
		else if (dir == 1 && cmdlist->next)
			cmdlist = cmdlist->next;
		else
			return (0);
	}
	if (cmdlist->type == syntype)
		return (1);
	return (0);
}
