/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 18:45:00 by sarchoi           #+#    #+#             */
/*   Updated: 2021/05/11 12:57:38 by sarchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}

static unsigned int	count_words(char const *str, char delim)
{
	unsigned int	count;

	count = 0;
	while (*str)
	{
		if (*str != delim)
		{
			count++;
			while (*str != delim && *str)
				str++;
			continue ;
		}
		str++;
	}
	return (count);
}

static unsigned int	ft_get_next_str_len(char const **str, char delim)
{
	unsigned int	i;

	while (**str)
	{
		if (**str != delim)
			break ;
		(*str)++;
	}
	i = 0;
	while ((*str)[i] != delim && (*str)[i])
		i++;
	return (i);
}

static char			**ft_malloc_error(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return ((char **)0);
}

char				**ft_split(char const *s, char c)
{
	char			**tab;
	unsigned int	i;
	unsigned int	str_count;
	unsigned int	str_len;

	i = 0;
	str_count = count_words(s, c);
	tab = (char **)malloc(sizeof(char *) * (str_count + 1));
	if (!tab)
		return ((char **)0);
	while (str_count > 0)
	{
		str_len = ft_get_next_str_len(&s, c);
		tab[i] = (char *)malloc(sizeof(char) * (str_len + 1));
		if (!tab[i])
			return (ft_malloc_error(tab));
		tab[i] = ft_strncpy(tab[i], s, str_len);
		s += str_len;
		tab[i][str_len] = '\0';
		i++;
		str_count--;
	}
	tab[i] = (char *)0;
	return (tab);
}
