/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:39:03 by cpak              #+#    #+#             */
/*   Updated: 2022/05/09 16:33:49 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	deal_cmd_node(t_cmd *cmd)
{
	char	**command;
	int		idx;
	int		result;

	result = 1;
	command = cmd->strarr;
	if (cmd->op == PIPE)
	{
		idx = exec_assign(command, cmd);
		if (idx == -1 || !command[idx])
			return (1);
		if (!exec_builtin(command))
			exec_execve(command);
	}
	else if (cmd->op == INPUT || cmd->op == INPUT_D)
		result = exec_input_redir(command, cmd->op);
	else if (cmd->op == OUTPUT || cmd->op == OUTPUT_D)
		result = exec_output_redir(command, cmd->op);
	return (result);
}

static int	deal_syntax_error(void)
{
	if (g_mini.exit_status == 94 || g_mini.exit_status == 95)
	{
		if (g_mini.exit_status == 95)
			ft_putstr_fd("minishell: syntax error: unexpected token\n", 2);
		if (g_mini.exit_status == 94)
			ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		g_mini.syntax_error = 1;
		g_mini.exit_status = 0;
		return (0);
	}
	return (1);
}

int	deal_command(void)
{
	t_cmd	*cmd;

	if (!g_mini.prompt_input || !*g_mini.prompt_input)
		return (0);
	if (!set_cmd_list(g_mini.prompt_input))
	{
		free_global();
		exit(1);
	}
	if (!deal_syntax_error())
		return (0);
	g_mini.cmd_idx = 1;
	cmd = g_mini.cmd;
	while (cmd)
	{
		if (!deal_cmd_node(cmd))
			return (0);
		cmd = cmd->next;
		g_mini.cmd_idx += 1;
	}
	if (g_mini.syntax_error)
		g_mini.syntax_error = 0;
	return (1);
}
