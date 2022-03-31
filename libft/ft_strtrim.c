/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 18:32:55 by sarchoi           #+#    #+#             */
/*   Updated: 2021/05/07 14:32:21 by sarchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_is_char_in_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static int			ft_find_start_len(
	char const **s1, char const **set, unsigned int *len)
{
	char const		*s_end;

	s_end = *s1 + (ft_strlen(*s1) - 1);
	while (ft_is_char_in_set(**s1, *set))
		(*s1)++;
	while (ft_is_char_in_set(*s_end, *set))
		s_end--;
	if (s_end < *s1)
		return (0);
	*len = s_end - (*s1) + 1;
	return (1);
}

char				*ft_strtrim(char const *s1, char const *set)
{
	char			*r;
	unsigned int	s_len;
	unsigned int	i;

	if (!ft_find_start_len(&s1, &set, &s_len))
	{
		r = (char *)malloc(sizeof(char) * 1);
		r[0] = '\0';
		return (r);
	}
	r = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!r)
		return ((char *)0);
	i = 0;
	while (i < s_len)
	{
		r[i] = s1[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}
