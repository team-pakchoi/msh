/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 00:04:18 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/05 00:26:29 by sarchoi          ###   ########seoul.kr  */
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

int	ft_exit(char **args)
{
	if (!args[0])
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	if (args[0] && str_isdigit(args[0]))
	{
		printf("exit with number\n");
		exit((unsigned char)ft_atol(args[0]));
	}
	if (args[0] && args[1])
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		return (FT_ERROR);
	}
	ft_putstr_fd("exit\nminishell: exit: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
	return (FT_ERROR);
}
