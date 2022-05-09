/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:38:47 by cpak              #+#    #+#             */
/*   Updated: 2022/05/09 04:13:24 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_nums_splited(char *str, int (*sep_func)(char *, int *))
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

static char	*get_str(char *str, int len)
{
	char	*result;

	result = (char *)ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (0);
	ft_strlcpy(result, str, len);
	return (result);
}

static int	set_splited_arr(char *str, char ***result, int nums,
								int (*sep_func)(char *, int *))
{
	int		idx;
	int		len;
	int		sep;

	idx = 0;
	sep = 0;
	while (idx < nums)
	{
		len = get_len_to_next(&str, sep_func);
		(*result)[idx] = get_str(str, len + 1);
		if (!(*result)[idx])
			return (0);
		str += sep_func(str + len, &sep) + len;
		idx += 1;
	}
	(*result)[nums] = 0;
	return (1);
}

char	**split_with_quote(char *str, int (*sep_func)(char *, int *))
{
	char	**result;
	int		nums_splited;

	nums_splited = get_nums_splited(str, sep_func);
	result = (char **)ft_calloc(nums_splited + 1, sizeof(char *));
	if (result == 0)
		return (0);
	if (!set_splited_arr(str, &result, nums_splited, sep_func))
	{
		ft_free_arr(result);
		return (0);
	}
	return (result);
}
