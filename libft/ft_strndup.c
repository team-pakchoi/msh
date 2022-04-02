/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 21:31:38 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/01 22:05:44 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *src, size_t n)
{
	char			*dup;
	char			*dup_start;
	unsigned int	len;
	unsigned int	i;

	len = ft_strlen(src);
	if (len < n)
		n = len;
	dup = (char *)malloc(sizeof(char) * (n + 1));
	if (!dup)
		return (0);
	dup_start = dup;
	i = 0;
	while (*src && i < n)
	{
		*dup = *src;
		src++;
		dup++;
		i++;
	}
	*dup = '\0';
	return (dup_start);
}
