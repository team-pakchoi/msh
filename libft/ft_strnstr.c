/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 11:58:24 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/28 03:21:13 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_same(const char *str, const char *to_find, size_t len)
{
	while (*str && *to_find && len && *str == *to_find)
	{
		str++;
		to_find++;
		len--;
	}
	if (!*to_find)
		return (1);
	if (*to_find && (!*str || !len))
		return (0);
	return (0);
}

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	if (!*to_find)
		return ((char *)str);
	while (*str && len)
	{
		if (*str == *to_find)
		{
			if (is_same(str + 1, to_find + 1, len - 1))
				return ((char *)str);
		}
		str++;
		len--;
	}
	return ((char *)0);
}
