/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:39:03 by cpak              #+#    #+#             */
/*   Updated: 2022/04/06 14:39:04 by cpak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_white_space(char *str, int *sep_num)
{
    if (*str == 32)
        *sep_num = 1;
    else
        *sep_num = 0;
    return (*sep_num);
}

int deal_cmd_node(t_cmd *cmd)
{
	char	**command;
    
    command = split_with_quote_flag(cmd->str, is_white_space);
    parse_cmd_env(command);
    if (cmd->op == PIPE)
    {
        if (exe_builtin(command) == 0)
            exe_execve(command);
    }
    else if (cmd->op == INPUT || cmd->op == INPUT_D)
        exe_input_redir(command, cmd->op);
    else if (cmd->op == OUTPUT || cmd->op == OUTPUT_D)
        exe_output_redir(command);
	return (1);
}

int deal_command(char *str)
{
    t_cmd   *cmd;

    if (str == 0 || *str == 0)
        return (0);
    if (set_cmd_list(str) == 0)
        return (0);
    g_mini.cmd_idx = 1;
    cmd = g_mini.cmd;
    while (cmd)
    {
        deal_cmd_node(cmd);
        cmd = cmd->next;
        g_mini.cmd_idx += 1;
    }
    return (1);
}
