/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 13:17:37 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/25 16:38:14 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_unset(char *name)
{
	if (!is_valid_var_name(name))
	{
		print_error2("unset", name, "is not a valid identifier");
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
		execute_unset(*cmds);
		cmds++;
	}
}
