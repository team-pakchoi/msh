/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 18:29:43 by sarchoi           #+#    #+#             */
/*   Updated: 2021/05/11 12:59:44 by sarchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*r;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	r = (char *)malloc(s1_len + s2_len + 1);
	if (!r)
		return ((char *)0);
	ft_strlcpy(r, s1, s1_len + 1);
	ft_strlcpy(r + s1_len, s2, s2_len + 1);
	*(r + s1_len + s2_len) = '\0';
	return (r);
}
