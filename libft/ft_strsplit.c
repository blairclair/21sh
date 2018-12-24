/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 10:23:42 by agrodzin          #+#    #+#             */
/*   Updated: 2018/03/22 15:22:24 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_word_count(char *s, char c)
{
	int n;
	int	i;

	n = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			while (s[i] == c && s[i])
				i++;
		else
		{
			n++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (n);
}

static int		largest_word(char *s, char c)
{
	int i;
	int	j;
	int largest;

	j = 0;
	largest = 0;
	while (s[j])
	{
		i = 0;
		if (s[j] == c)
			while (s[j] == c && s[j])
				j++;
		while (s[j] != c && s[j])
		{
			i++;
			j++;
		}
		if (i > largest)
			largest = i;
	}
	return (largest);
}

static char		**hi(int i, char **st_arr, char *s, char c)
{
	int	l;
	int	j;
	int k;

	k = 0;
	j = 0;
	while (s[i])
	{
		l = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			st_arr[j][l] = s[i];
			l++;
			i++;
		}
		if (s[i] == c)
		{
			st_arr[j][l] = '\0';
			j++;
		}
	}
	return (st_arr);
}

char			**ft_strsplit(char *s, char c)
{
	char	**st_arr;
	int		i;
	int		j;
	int		words;
	int		lg;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	words = get_word_count(s, c) + 1;
	lg = largest_word(s, c) + 1;
	st_arr = (char **)ft_memalloc(sizeof(char*) * words);
	if (!st_arr)
		return (NULL);
	while (j < words - 1)
	{
		st_arr[j] = (char*)ft_memalloc(sizeof(char*) * lg);
		if (!st_arr[j])
			return (NULL);
		j++;
	}
	st_arr[words - 1] = NULL;
	st_arr = hi(i, st_arr, s, c);
	return (st_arr);
}
