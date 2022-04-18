/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 14:20:03 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/16 21:05:19 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_export(char *name)
{
	t_var	*tmp;

	if (!is_valid_var_name(name))
	{
		print_error2("export", name, "not a valid identifier");
		g_mini.exit_status = 1;
		return ;
	}
	tmp = find_var(name);
	if (ft_strchr(name, '='))
	{
		if (tmp)
			update_var(ft_strndup(name, ft_strchr(name, '=') - name), ft_strchr(name, '=') + 1);
		else
			add_var(name, ENV_VAR);
		return ;
	}
	if (!tmp)
		return ;
	tmp->scope = ENV_VAR;
}

void	ft_export(char **cmds)
{
	g_mini.exit_status = 0;
	if (!cmds[1])
	{
		ft_env();
		return ;
	}
	while (*cmds)
	{
		execute_export(*cmds);
		cmds++;
	}
}
