/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 13:17:37 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/14 17:27:59 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_export(char *name)
{
	if (!is_valid_var_name(name))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_mini.exit_status = 1;
		return ;
	}
	if (!find_var_value(name))
	{
		g_mini.exit_status = 0;
		return ;
	}
	remove_var(name);
	g_mini.exit_status = 0;
}

void	ft_unset(char **cmds)
{
	if (!cmds[1])
	{
		g_mini.exit_status = 0;
		return ;
	}
	while (*cmds)
	{
		execute_export(*cmds);
		cmds++;
	}
}
