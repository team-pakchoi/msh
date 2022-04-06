/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 16:59:56 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/06 00:48:19 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **cmds)
{
	int	is_n_option;

	is_n_option = FT_FALSE;
	cmds++;
	if (*cmds && ft_strcmp(*cmds, "-n") == 0)
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
