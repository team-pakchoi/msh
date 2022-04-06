/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 14:20:03 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/05 17:19:55 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(char **cmds)
{
	t_var	*tmp;

	g_mini.exit_status = 0;
	if (!cmds[1])
	{
		ft_env();
		return ;
	}
	if (!is_valid_var_name(cmds[1]))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(cmds[1], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_mini.exit_status = 1;
		return ;
	}
	tmp = find_var(cmds[1]);
	if (ft_strchr(cmds[1], '='))
	{
		if (tmp)
			update_var(ft_strndup(cmds[1], ft_strchr(cmds[1], '=') - cmds[1]), ft_strchr(cmds[1], '=') + 1);
		else
			add_var(cmds[1], ENV_VAR);
		return ;
	}
	if (!tmp)
		return ;
	tmp->scope = ENV_VAR;
}
