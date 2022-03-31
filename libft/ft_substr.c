/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 18:21:14 by sarchoi           #+#    #+#             */
/*   Updated: 2021/05/09 12:29:04 by sarchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*r;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start > s_len)
	{
		r = (char *)malloc(sizeof(char));
		*r = '\0';
		return (r);
	}
	if (s_len > len)
		s_len = len;
	r = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!r)
		return ((char *)0);
	ft_strlcpy(r, s + start, len + 1);
	return (r);
}
