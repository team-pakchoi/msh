/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:39:03 by cpak              #+#    #+#             */
/*   Updated: 2022/05/11 14:45:26 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	deal_syntax_error(void)
{
	if (g_mini.exit_status == 258)
	{
		ft_putstr_fd("minishell: syntax error: unexpected token\n", 2);
		return (0);
	}
	if (g_mini.has_redir_error)
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		g_mini.has_redir_error = 0;
		return (0);
	}
	return (1);
}

int	exec_cmd_node(t_cmd *cmd)
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
		if (!exec_builtin(command, is_builtin(command)))
			exec_execve(command);
	}
	else if (cmd->op == INPUT || cmd->op == INPUT_D)
		result = exec_input_redir(command, cmd->op);
	else if (cmd->op == OUTPUT || cmd->op == OUTPUT_D)
		result = exec_output_redir(command, cmd->op);
	return (result);
}

static int	exec_single_cmd(void)
{
	t_cmd	*cmd;
	pid_t	pid;
	int		status;

	cmd = find_nth_cmd(0);
	if (cmd->op == PIPE && !is_builtin(cmd->strarr))
	{
		pid = fork();
		if (pid == 0)
		{
			g_mini.is_main_process = FT_FALSE;
			exec_cmd_node(cmd);
			return (1);
		}
		waitpid(pid, &status, 0);
		set_exit_status(status);
	}
	else
		exec_cmd_node(cmd);
	return (1);
}

static int	exec_command(void)
{
	t_cmd	*cmd;
	int		result;

	cmd = find_cmd_has_heredoc();
	if (cmd)
		write_prompt_to_heredoc(cmd->strarr[0]);
	if (g_mini.cmd_len == 1)
		result = exec_single_cmd();
	else
		result = exec_multi_cmd();
	return (result);
}

int	deal_command(void)
{
	if (!g_mini.prompt_input || !*g_mini.prompt_input)
		return (0);
	if (!parse_prompt_input(g_mini.prompt_input))
	{
		free_global();
		exit(1);
	}
	if (!deal_syntax_error())
		return (0);
	exec_command();
	return (1);
}
