/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 11:57:27 by sarchoi           #+#    #+#             */
/*   Updated: 2021/05/09 12:11:11 by sarchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	unsigned char	uc;

	d = dst;
	s = (unsigned char *)src;
	uc = c;
	while (n)
	{
		*d = *s;
		d++;
		if (*s == uc)
			return (d);
		s++;
		n--;
	}
	return ((void *)0);
}
