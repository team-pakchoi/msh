/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:59:56 by sarchoi           #+#    #+#             */
/*   Updated: 2022/05/03 19:01:40 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_n_option(char *str)
{
	int	idx;

	idx = 1;
	if (str[0] != '-' || str[1] != 'n')
		return (0);
	while (str[idx] && str[idx] == 'n')
		idx += 1;
	if (str[idx])
		return (0);
	return (1);
}

void	ft_echo(char **cmds)
{
	int	is_n_option;

	is_n_option = FT_FALSE;
	cmds++;
	if (*cmds && check_n_option(*cmds))
	{
		is_n_option = FT_TRUE;
		cmds++;
	}
	while (*cmds)
	{
		ft_putstr_fd(*cmds, 1);
		cmds++;
		if (*cmds)
			ft_putchar_fd(' ', 1);
	}
	if (!is_n_option)
		ft_putchar_fd('\n', 1);
	g_mini.exit_status = 0;
}
