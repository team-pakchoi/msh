/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 00:04:18 by sarchoi           #+#    #+#             */
/*   Updated: 2022/05/04 16:47:09 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	str_isdigit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (FT_FALSE);
		i++;
	}
	return (FT_TRUE);
}

void	ft_exit(char **cmds)
{
	if (cmds[1] && !str_isdigit(cmds[1]))
	{
		ft_putstr_fd("exit\n", 2);
		print_error2("exit", cmds[1], "numeric argument required");
		g_mini.exit_status = 255;
		exit(g_mini.exit_status);
	}
	if (cmds[1] && cmds[2])
	{
		ft_putstr_fd("exit\n", 2);
		print_error("exit", "too many arguments");
		g_mini.exit_status = 1;
		return ;
	}
	if (cmds[1] && str_isdigit(cmds[1]))
	{
		ft_putstr_fd("exit\n", 1);
		g_mini.exit_status = ft_atoi(cmds[1]);
		exit(g_mini.exit_status);
	}
	ft_putstr_fd("exit\n", 1);
	g_mini.exit_status = 0;
	exit(g_mini.exit_status);
}
