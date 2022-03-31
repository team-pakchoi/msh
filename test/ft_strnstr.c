/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 12:17:54 by cpak              #+#    #+#             */
/*   Updated: 2022/03/31 15:33:22 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strnstr(const char *haystack, const char *needle, unsigned int len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (haystack[i] && needle[j] && i + j < len)
	{
		if (haystack[i + j] == needle[j])
			j++;
		else if (haystack[i + j] != needle[j])
		{
			j = 0;
			i++;
		}
	}
	if (needle[j])
		return (0);
	return ((char *)haystack + i);
}
