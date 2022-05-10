/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 00:09:03 by cpak              #+#    #+#             */
/*   Updated: 2022/05/10 16:50:14 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char **cmd)
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

int	exec_builtin(char **cmd, int n)
{
	if (n == 0)
		return (0);
	else if (n == 1)
		ft_cd(cmd);
	else if (n == 2)
		ft_echo(cmd);
	else if (n == 3)
		ft_env();
	else if (n == 4)
		ft_exit(cmd);
	else if (n == 5)
		ft_export(cmd);
	else if (n == 6)
		ft_pwd();
	else if (n == 7)
		ft_unset(cmd);
	return (1);
}
