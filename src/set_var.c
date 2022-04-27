/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:13:09 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/27 15:52:50 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_set(char *name)
{
	t_var	*tmp;
	char	*tmp_name;

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
		{
			tmp_name = ft_strndup(name, ft_strchr(name, '=') - name);
			update_var(tmp_name, ft_strchr(name, '=') + 1);
			free(tmp_name);
		}
		else
			add_var(name, SHELL_VAR);
		return ;
	}
	if (!tmp)
		return ;
	tmp->scope = SHELL_VAR;
}

void	set_var(char **cmds)
{
	g_mini.exit_status = 0;
	// if (!cmds[1])
	// {
	// 	ft_env();
	// 	return ;
	// }
	while (*cmds)
	{
		execute_set(*cmds);
		cmds++;
	}
}
