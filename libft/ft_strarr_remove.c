/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 03:19:14 by cpak              #+#    #+#             */
/*   Updated: 2022/05/05 22:17:29 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strarr_remove(char ***strarr, int len, int tar_idx)
{
	char	**new_arr;
	int		idx_n;
	int		idx;

	new_arr = (char **)ft_calloc(len, sizeof(char **));
	if (!new_arr)
		return (0);
	idx = 0;
	idx_n = 0;
	while (idx < len)
	{
		if (idx != tar_idx)
		{
			new_arr[idx_n] = (*strarr)[idx];
			idx_n += 1;
		}
		else
			free((*strarr)[idx]);
		idx += 1;
	}
	free(*strarr);
	*strarr = new_arr;
	return (1);
}
