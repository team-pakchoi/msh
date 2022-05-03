/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_remove.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 03:19:14 by cpak              #+#    #+#             */
/*   Updated: 2022/05/03 03:30:36 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strarr_remove(char ***strarr, int tar_idx)
{
	char	**new_arr;
	int		len;
	int		idx_n;
	int		idx;

	len = ft_strarr_len(*strarr) - 1;
	new_arr = (char **)ft_calloc(len + 1, sizeof(char **));
	if (!new_arr)
		return (0);
	idx = 0;
	idx_n = 0;
	while ((*strarr)[idx])
	{
		new_arr[idx_n] = (*strarr)[idx];
		if (idx != tar_idx)
			idx_n += 1;
		idx += 1;
	}
	free(*strarr);
	*strarr = new_arr;
	return (1);
}
