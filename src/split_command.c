/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:13:25 by cpak              #+#    #+#             */
/*   Updated: 2022/01/28 17:10:47 by cpak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_quotes(char *s)
{
	if (s == 0)
		return (0);
	while (*s)
	{
		if (*s == 34)
			return (34);
		if (*s == 39)
			return (39);
		s += 1;
	}
	return (0);
}

int	get_arr_len(char **arr)
{
	int	len;

	len = 0;
	while (arr[len])
		len += 1;
	return (len);
}

char	**join_arr(char **arr1, char **arr2, int is_front)
{
	char	**tar;
	int		arr1_len;
	int		arr2_len;
	int		idx;

	arr1_len = get_arr_len(arr1);
	arr2_len = get_arr_len(arr2);
	if (is_front)
	{
		arr2_len -= 1;
		arr2 += 1;
	}
	else
		arr1_len -= 1;
	tar = (char **)malloc(sizeof(char *) * (arr1_len + arr2_len + 1));
	if (tar == 0)
		return (0);
	idx = -1;
	while (++idx < arr1_len)
		tar[idx] = arr1[idx];
	idx = -1;
	while (++idx < arr2_len)
		tar[idx + arr1_len] = arr2[idx];
	tar[arr1_len + arr2_len] = 0;
	return (tar);
}

char	**set_last_split(char **arr1, char **arr2, char **arr3)
{
	char	**result;

	arr2 = ft_split(arr1[2], 32);
	free(arr1[2]);
	free(arr1);
	result = join_arr(arr3, arr2, 0);
	free(arr3);
	free(arr2);
	return (result);
}

char	**split_command(char *cmd)
{
	char	**arr1;
	char	**arr2;
	char	**arr3;
	int		has_quotes;

	has_quotes = find_quotes(cmd);
	if (has_quotes == 0)
		return (ft_split(cmd, 32));
	arr1 = ft_split(cmd, has_quotes);
	arr2 = ft_split(arr1[0], 32);
	free(arr1[0]);
	arr3 = join_arr(arr2, arr1, 1);
	free(arr2);
	if (has_quotes != 0 && arr1[2] != 0)
		return (set_last_split(arr1, arr2, arr3));
	free(arr1);
	return (arr3);
}
