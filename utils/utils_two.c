/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 11:10:25 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/23 11:10:28 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_shell.h"

int		is_builtin(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (!ft_strcmp(str, "cd") || !ft_strcmp(str, "echo") ||
			!ft_strcmp(str, "exit") || !ft_strcmp(str, "env") ||
			!ft_strcmp(str, "setenv") || !ft_strcmp(str, "unsetenv"))
		return (1);
	return (0);
}

char	**deepcopy(char **data)
{
	size_t	i;
	size_t	j;
	char	*c;
	char	**res;

	if (data)
	{
		i = -1;
		c = data[0];
		while (c != 0)
			c = data[++i];
		res = ft_memalloc(sizeof(char*) * i + 10);
		j = -1;
		while (++j < i)
		{
			res[j] = ft_memalloc(strlen(data[j]) + 1);
			ft_strcpy(res[j], data[j]);
		}
	}
	else
		res = ft_memalloc(20);
	return (res);
}

void	add_to_end(t_execute **head, int status, char **data, t_tok_type type)
{
	t_execute	*newnode;
	t_execute	*last;

	newnode = (t_execute*)ft_memalloc(sizeof(t_execute));
	last = (*head);
	newnode->status = status;
	newnode->data = deepcopy(data);
	newnode->type = type;
	newnode->next = NULL;
	if (*head == NULL)
	{
		newnode->prev = NULL;
		(*head) = newnode;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = newnode;
	newnode->prev = last;
}

int		ft_isdelim(char c)
{
	if (c == ';' || c == '&' || c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}
