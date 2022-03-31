/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 18:41:44 by cpak              #+#    #+#             */
/*   Updated: 2022/03/31 15:33:27 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	getlen_s1(char const *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	check_set(char const *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

int	find_point(char const *s, char const *set, int i, int dir)
{
	while (check_set(set, s[i]))
		i += dir;
	if (dir < 0)
		i++;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		s1_len;
	int		start;
	int		end;
	int		i;

	if (s1 == 0 || set == 0)
		return (0);
	s1_len = getlen_s1(s1);
	start = find_point(s1, set, 0, 1);
	if (s1_len == start)
	{
		result = (char *)malloc(sizeof(char) * 1);
		result[0] = 0;
		return (result);
	}
	end = find_point(s1, set, s1_len - 1, -1);
	result = (char *)malloc((end - start) + 1 * sizeof(char));
	if (result == 0)
		return (0);
	i = 0;
	while (start < end)
		result[i++] = s1[start++];
	result[i] = 0;
	return (result);
}
