/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:39:17 by cpak              #+#    #+#             */
/*   Updated: 2022/05/11 13:26:12 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_input_redir_node(t_cmd *node)
{
	t_cmd	*tar;
	t_cmd	*prev_tar;

	tar = find_last_cmd();
	while (tar->prev != 0 && tar->op != 1)
		tar = tar->prev;
	if (tar->prev == 0)
	{
		g_mini.cmd = node;
		node->next = tar;
		tar->prev = node;
		return (1);
	}
	prev_tar = tar->prev;
	prev_tar->next = node;
	node->prev = prev_tar;
	node->next = tar;
	tar->prev = node;
	return (1);
}

static int	set_output_redir_node(t_cmd *node)
{
	t_cmd	*tar;
	t_cmd	*next_tar;

	tar = find_last_cmd();
	while (tar->prev != 0 && tar->op != 1)
		tar = tar->prev;
	next_tar = tar->next;
	if (tar->next != 0)
		next_tar->prev = node;
	node->next = next_tar;
	node->prev = tar;
	tar->next = node;
	return (1);
}

int	add_cmd(char **strarr, t_op op)
{
	t_cmd	*new;
	t_cmd	*last;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	new->strarr = strarr;
	new->op = op;
	new->next = 0;
	new->prev = 0;
	last = find_last_cmd();
	g_mini.cmd_len += 1;
	if (last == 0)
		g_mini.cmd = new;
	else
	{
		if (op == INPUT || op == INPUT_D)
			return (set_input_redir_node(new));
		else if (op == OUTPUT || op == OUTPUT_D)
			return (set_output_redir_node(new));
		last->next = new;
		new->prev = last;
	}
	return (1);
}

void	remove_cmd_list(void)
{
	t_cmd	*node;
	t_cmd	*prev;

	node = g_mini.cmd;
	while (node)
	{
		prev = node;
		node = node->next;
		ft_free_arr(prev->strarr);
		prev->strarr = 0;
		prev->next = 0;
		prev->prev = 0;
		free(prev);
	}
	g_mini.cmd = 0;
	g_mini.cmd_len = 0;
}

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
