/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:13:26 by cpak              #+#    #+#             */
/*   Updated: 2022/03/31 15:33:06 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_size(char const *s, char c)
{
	int		ischar;
	int		size;

	ischar = 0;
	size = 0;
	while (*s)
	{
		if (ischar == 0 && *s != c)
		{
			ischar = 1;
			size++;
		}
		else if (ischar == 1 && *s == c)
		{
			ischar = 0;
		}
		s++;
	}
	return (size);
}

int	get_len_c(char const *s, char c)
{
	int		len;

	len = 0;
	while (s[len] != c && s[len])
		len++;
	return (len);
}

int	split_and_push(char **arr, char const *s, char c, int size)
{
	char	*splited;
	int		len;
	int		i;

	if (size != 0)
	{
		while (*s == c)
			s++;
		len = get_len_c(s, c);
		splited = (char *)malloc(sizeof(char) * (get_len_c(s, c) + 1));
		if (splited == 0)
			return (0);
		i = 0;
		while (i < len)
		{
			splited[i] = s[i];
			i++;
		}
		splited[i] = 0;
		*arr = splited;
		s += i;
		return (split_and_push(arr + 1, s, c, size - 1));
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		size;

	if (s == 0 || c == 0)
		return (0);
	size = get_size(s, c);
	result = (char **)malloc(sizeof(char *) * (size + 1));
	if (result == 0)
		return (0);
	if (split_and_push(result, s, c, size) == 0)
		return (0);
	result[size] = 0;
	return (result);
}
