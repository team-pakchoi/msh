/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 00:04:18 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/06 00:18:32 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	str_isdigit(char *str)
{
	int	i;

	i = 0;
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
	printf("exit\n");
	if (cmds[1] && !str_isdigit(cmds[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmds[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_mini.exit_status = 255;
		exit(g_mini.exit_status);
	}
	if (cmds[1] && cmds[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_mini.exit_status = 1;
		return ;
	}
	if (cmds[1] && str_isdigit(cmds[1]))
	{
		g_mini.exit_status = ft_atoi(cmds[1]);
		exit(g_mini.exit_status);
	}
	g_mini.exit_status = 0;
	exit(g_mini.exit_status);
}
