/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 00:04:18 by sarchoi           #+#    #+#             */
/*   Updated: 2022/05/08 01:23:13 by sarchoi          ###   ########seoul.kr  */
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

static int	ft_isspace(int c)
{
	if (c == ' ' || (9 <= c && c <= 13))
		return (1);
	return (0);
}

static int	check_range(const char *str)
{
	unsigned long long	r;
	long long			sign;

	r = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		r = r * 10 + (*str - '0');
		if (sign == 1 && r > 9223372036854775807U)
			return (FT_FALSE);
		else if (sign == -1 && r > 9223372036854775808U)
			return (FT_FALSE);
		str++;
	}
	return (FT_TRUE);
}

static void	too_many_args(char *str)
{
	ft_putstr_fd("exit\n", 2);
	print_error("exit", "too many arguments");
	g_mini.exit_status = 1;
	free(str);
}

void	ft_exit(char **cmds)
{
	char	*str;

	if (!cmds[1])
	{
		g_mini.exit_status = 0;
		exit_with_status();
	}
	str = ft_strtrim(cmds[1], " ");
	if (!str_isdigit(str) || !check_range(str))
	{
		ft_putstr_fd("exit\n", 2);
		print_error2("exit", cmds[1], "numeric argument required");
		free(str);
		g_mini.exit_status = 255;
		exit(g_mini.exit_status);
	}
	if (cmds[2])
	{
		too_many_args(str);
		return ;
	}
	g_mini.exit_status = ft_atoi(str);
	free(str);
	exit_with_status();
}
