/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_assign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 04:41:40 by cpak              #+#    #+#             */
/*   Updated: 2022/04/28 04:45:16 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_assign_cmd(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		if (!ft_isalpha(str[idx]) && !ft_isdigit(str[idx]) && str[idx] != '_')
			break ;
		idx += 1;
	}
	return (str[idx] == '=');
}

int	exec_assign(char **command, t_cmd *cmd)
{
	int	idx;

	idx = 0;
	while (command[idx])
	{
		if (!is_assign_cmd(command[idx]))
			break ;
		idx += 1;
	}
	if (!command[idx])
	{
		if (cmd->prev && cmd->prev->op == 1)
			return (-1);
		if (cmd->next && cmd->next->op == 1)
			return (-1);
		set_var(command);
		set_self_pipe();
		restore_ori_stdout();
	}
	return (idx);
}
