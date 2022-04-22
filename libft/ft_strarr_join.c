/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 19:32:30 by cpak              #+#    #+#             */
/*   Updated: 2022/04/01 19:32:39 by cpak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    **ft_strarr_join(char *a1[], char *a2[])
{
    size_t	a1_len;
	size_t	a2_len;
	char	**r;

	a1_len = ft_strarr_len(a1);
	a2_len = ft_strarr_len(a2);
	r = (char **)malloc(sizeof(char **) * (a1_len + a2_len + 1));
	if (!r)
		return ((char **)0);
	ft_strarr_lcpy(r, a1, a1_len + 1);
	ft_strarr_lcpy(r + a1_len, a2, a2_len + 1);
	*(r + a1_len + a2_len) = (char *)0;
	return (r);
}