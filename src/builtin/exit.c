/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 00:04:18 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/05 00:04:22 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_range(int n)
{
	if (n < 0 || 255 < n)
		return (FT_ERROR);
	return (FT_SUCCESS);
}

int	ft_exit(char **args)
{
	if (!args[0])
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	if (args[0] && check_range(ft_atoi(args[0])) == FT_ERROR)
	{
		ft_putstr_fd("exit\nminishell: exit: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	if (args[0] && args[1])
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		return (FT_ERROR);
	}
	if (args[0] && check_range(ft_atoi(args[0])) == FT_SUCCESS)
	{
		printf("exit with number\n");
		exit((unsigned char)ft_atoi(args[0]));
	}
	return (FT_SUCCESS);
}
