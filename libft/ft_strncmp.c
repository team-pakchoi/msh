/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 11:58:22 by sarchoi           #+#    #+#             */
/*   Updated: 2021/05/05 16:14:16 by sarchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*s1_u;
	const unsigned char	*s2_u;
	size_t				i;

	s1_u = (void *)s1;
	s2_u = (void *)s2;
	if (!n)
		return (0);
	i = 0;
	while (i < n && (s1_u[i] || s2_u[i]))
	{
		if (s1_u[i] != s2_u[i])
			return (s1_u[i] - s2_u[i]);
		i++;
	}
	if (i == n || s1_u[i] == s2_u[i])
		return (0);
	else
		return (s1_u[i] - s2_u[i]);
}
