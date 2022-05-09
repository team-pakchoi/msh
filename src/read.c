/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 21:00:01 by cpak              #+#    #+#             */
/*   Updated: 2022/05/09 13:36:37 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_arr(char **arr)
{
	int	idx;

	idx = 0;
	while (arr[idx])
	{
		printf("idx: %d\n", idx);
		printf("|%s|\n", arr[idx]);
		idx += 1;
	}
	printf("=\n");
}

void	read_cmd_list(void)
{
	t_cmd	*node;

	node = g_mini.cmd;
	printf("----cmd----\n");
	while (node != 0)
	{
		printf("op: %d\n", node->op);
		printf("-\n");
		read_arr(node->strarr);
		node = node->next;
	}
	printf("----cmd----\n");
}
