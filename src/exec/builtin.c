/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 00:09:03 by cpak              #+#    #+#             */
/*   Updated: 2022/05/08 03:53:18 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(char **cmd)
{
	if (!ft_strcmp(*cmd, "cd"))
		return (1);
	if (!ft_strcmp(*cmd, "echo"))
		return (2);
	if (!ft_strcmp(*cmd, "env"))
		return (3);
	if (!ft_strcmp(*cmd, "exit"))
		return (4);
	if (!ft_strcmp(*cmd, "export"))
		return (5);
	if (!ft_strcmp(*cmd, "pwd"))
		return (6);
	if (!ft_strcmp(*cmd, "unset"))
		return (7);
	return (0);
}

static void	route_builtin(char **cmd, int n)
{
	if (n == 1)
		return (ft_cd(cmd));
	if (n == 2)
		return (ft_echo(cmd));
	if (n == 3)
		return (ft_env());
	if (n == 4)
		return (ft_exit(cmd));
	if (n == 5)
		return (ft_export(cmd));
	if (n == 6)
		return (ft_pwd());
	if (n == 7)
		return (ft_unset(cmd));
}

int	exec_builtin(char **cmd)
{
	int	n;

	n = is_builtin(cmd);
	if (n)
	{
		if (g_mini.cmd_len != g_mini.cmd_idx)
			set_self_pipe();
		route_builtin(cmd, n);
		restore_ori_stdout();
	}
	return (n);
}
