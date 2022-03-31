/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:37:24 by cpak              #+#    #+#             */
/*   Updated: 2022/03/31 15:33:15 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	getlen_s(char const *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		s1_len;
	int		s2_len;
	int		i;

	if (s1 == 0 || s2 == 0)
		return (0);
	s1_len = getlen_s(s1);
	s2_len = getlen_s(s2);
	result = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (result == 0)
		return (0);
	if (s1_len + s2_len == 0)
		result[0] = 0;
	i = 0;
	while (i < s1_len)
		result[i++] = *s1++;
	while (i < (s1_len + s2_len))
		result[i++] = *s2++;
	result[i] = 0;
	return (result);
}
