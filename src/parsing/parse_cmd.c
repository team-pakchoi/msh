/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 05:50:03 by cpak              #+#    #+#             */
/*   Updated: 2022/05/09 05:50:25 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_cmd(char ***strarr)
{
	int	idx;
	int	sep;
	int	arr_len;

	idx = 0;
	arr_len = ft_strarr_len(*strarr);
	while ((*strarr)[idx])
	{
		sep = parse_str(&(*strarr)[idx]);
		if (sep == -1)
		{
			ft_free_arr(*strarr);
			return (0);
		}
		if (ft_strlen((*strarr)[idx]) == 0 && sep == 0)
		{
			ft_strarr_remove(strarr, arr_len, idx);
			arr_len -= 1;
		}
		else
			idx += 1;
	}
	return (1);
}
