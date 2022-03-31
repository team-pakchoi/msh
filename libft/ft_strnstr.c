/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 11:58:24 by sarchoi           #+#    #+#             */
/*   Updated: 2021/05/09 14:50:50 by sarchoi          ###   ########.fr       */
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

char		*ft_strnstr(const char *str, const char *to_find, size_t len)
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
