/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:11:30 by sarchoi           #+#    #+#             */
/*   Updated: 2022/05/11 13:11:51 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*find_nth_cmd(int idx)
{
	t_cmd	*node;

	node = g_mini.cmd;
	while (node != 0 && node->next != 0 && idx > 0)
	{
		node = node->next;
		idx -= 1;
	}
	return (node);
}

t_cmd	*find_last_cmd(void)
{
	t_cmd	*node;

	node = g_mini.cmd;
	while (node != 0 && node->next != 0)
		node = node->next;
	return (node);
}

t_cmd	*find_cmd_has_heredoc(void)
{
	int		idx;
	t_cmd	*cmd;

	idx = 0;
	while (idx < g_mini.cmd_len)
	{
		cmd = find_nth_cmd(idx);
		if (cmd->op == INPUT_D)
			return (cmd);
		idx += 1;
	}
	return (0);
}
