/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 11:58:09 by sarchoi           #+#    #+#             */
/*   Updated: 2021/05/05 12:10:26 by sarchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	srclen;
	size_t	destlen;
	size_t	i;
	size_t	j;

	srclen = ft_strlen(src);
	destlen = ft_strlen(dest);
	i = 0;
	j = destlen;
	while (*src && i + destlen + 1 < size)
	{
		*(dest + j) = *src;
		src++;
		i++;
		j++;
	}
	if (i + destlen < size)
		*(dest + j) = '\0';
	if (size < destlen)
		return (srclen + size);
	else
		return (srclen + destlen);
}
