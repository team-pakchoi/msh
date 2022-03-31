/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 11:57:39 by sarchoi           #+#    #+#             */
/*   Updated: 2021/05/07 22:00:43 by sarchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	copy_forwards(unsigned char *dst,
const unsigned char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
}

static void	copy_reverse(unsigned char *dst,
const unsigned char *src, size_t len)
{
	int		i;

	i = len - 1;
	while (i >= 0)
	{
		dst[i] = src[i];
		i--;
	}
}

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!len || dst == src)
		return (dst);
	d = dst;
	s = src;
	if (d > s && d - s < (int)len)
	{
		copy_reverse(d, s, len);
		return (dst);
	}
	if (s > d && s - d < (int)len)
	{
		copy_forwards(d, s, len);
		return (dst);
	}
	ft_memcpy(dst, src, len);
	return (dst);
}
