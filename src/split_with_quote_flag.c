/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_quote_flag.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:38:47 by cpak              #+#    #+#             */
/*   Updated: 2022/04/28 07:25:05 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nums_splited(char *str, int (*sep_func)(char *, int *))
{
	int	nums;
	int	sep;
	int	len;

	nums = 0;
	sep = 0;
	while (*str)
	{
		len = get_len_to_next(&str, sep_func);
		if (len >= 1)
		{
			str += len;
			str += sep_func(str, &sep);
			nums += 1;
		}
	}
	return (nums);
}

char	*get_str(char *str, int len)
{
	char	*result;

	result = (char *)ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (0);
	ft_strlcpy(result, str, len);
	return (result);
}

char	**split_with_quote(char *str, int (*sep_func)(char *, int *))
{
	char	**result;
	int		nums_splited;
	int		idx;
	int		len;
	int		sep;

	nums_splited = get_nums_splited(str, sep_func);
	result = (char **)ft_calloc(nums_splited + 1, sizeof(char *));
	if (result == 0)
		return (0);
	idx = 0;
	sep = 0;
	while (idx < nums_splited)
	{
		len = get_len_to_next(&str, sep_func);
		result[idx] = get_str(str, len + 1);
		if (!result[idx])
			return (0);
		str += len;
		str += sep_func(str, &sep);
		idx += 1;
	}
	result[nums_splited] = 0;
	return (result);
}
