/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 13:17:37 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/05 16:31:34 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char **cmds)
{
	if (!cmds[1])
	{
		g_mini.exit_status = 0;
		return ;
	}
	if (!is_valid_var_name(cmds[1]))
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(cmds[1], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_mini.exit_status = 1;
		return ;
	}
	if (!find_var_value(cmds[1]))
	{
		g_mini.exit_status = 0;
		return ;
	}
	remove_var(cmds[1]);
	g_mini.exit_status = 0;
}
