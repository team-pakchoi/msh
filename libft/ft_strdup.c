/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 11:57:59 by sarchoi           #+#    #+#             */
/*   Updated: 2021/05/13 11:49:10 by sarchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char			*dup;
	char			*dup_start;
	unsigned int	len;

	len = ft_strlen(src);
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (0);
	dup_start = dup;
	while (*src)
	{
		*dup = *src;
		src++;
		dup++;
	}
	*dup = '\0';
	return (dup_start);
}
