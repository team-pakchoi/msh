/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_to_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 18:53:06 by cpak              #+#    #+#             */
/*   Updated: 2022/05/05 22:33:19 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	get_total_str_len(char *arr[], int len_arr, char *sep)
{
	int	len_total;
	int	idx;

	len_total = 0;
	idx = 0;
	while (idx < len_arr)
	{
		len_total += ft_strlen(arr[idx]);
		idx += 1;
	}
	len_total += (len_arr - 1) * ft_strlen(sep) + 1;
	return (len_total);
}

char	*ft_strarr_to_str(char *arr[], char *sep)
{
	int		len_arr;
	int		len_total;
	int		idx;
	char	*r;

	len_arr = ft_strarr_len(arr);
	r = (char *)calloc(get_total_str_len(arr, len_arr, sep), sizeof(char));
	if (!r)
		return ((char *)0);
	len_total = 0;
	idx = 0;
	while (idx < len_arr)
	{
		ft_strlcpy(r + len_total, arr[idx], ft_strlen(arr[idx]) + 1);
		len_total += ft_strlen(arr[idx]);
		idx += 1;
		if (idx < len_arr)
		{
			ft_strlcpy(r + len_total, sep, ft_strlen(sep) + 1);
			len_total += ft_strlen(sep);
		}
	}
	return (r);
}
