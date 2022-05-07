/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 04:54:47 by cpak              #+#    #+#             */
/*   Updated: 2022/05/05 22:06:24 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_args_to_prev_cmd(char **strarr)
{
	t_cmd	*node;
	char	**new_arr;

	node = find_last_cmd();
	if (node)
	{
		new_arr = ft_strarr_join(node->strarr, strarr);
		free(node->strarr);
		free(strarr);
		node->strarr = new_arr;
		return ;
	}
	add_cmd(strarr, 1);
}

static int	set_new_cmd(char **strarr, int sep)
{
	char	**shifted;

	if (sep != 1)
	{
		shifted = ft_strarr_shift(&strarr);
		set_args_to_prev_cmd(strarr);
		if (!add_cmd(shifted, sep))
			return (0);
	}
	else
	{
		if (!add_cmd(strarr, sep))
			return (0);
	}
	return (1);
}

static void	set_next_op(char **str, int *sep)
{
	*str += get_len_to_next(str, is_op);
	*str += is_op(*str, sep);
}

int	set_cmd_list(char *str)
{
	char	**arr;
	int		sep;
	char	**strarr;
	int		idx;

	while (is_white_space(str, &sep))
		str += 1;
	if (!is_op(str, &sep))
		sep = 1;
	idx = 0;
	arr = split_with_quote(str, is_op);
	while (arr[idx])
	{
		strarr = split_with_quote(arr[idx], is_white_space);
		if (!strarr)
			return (0);
		if (!parse_cmd(&strarr))
			return (0);
		if (!set_new_cmd(strarr, sep))
			return (0);
		set_next_op(&str, &sep);
		idx += 1;
	}
	ft_free_arr(arr);
	return (1);
}
