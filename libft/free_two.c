/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 11:16:39 by agrodzin          #+#    #+#             */
/*   Updated: 2018/11/23 11:16:54 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_two(char **arg, int start)
{
	int	i;

	i = start;
	if (arg == NULL)
		return ;
	while (arg[i])
	{
		free(arg[i]);
		arg[i] = NULL;
		i++;
	}
}
