/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 14:20:03 by sarchoi           #+#    #+#             */
/*   Updated: 2022/05/11 15:37:47 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_var_with_equal(t_var *tmp, char *name)
{
	char	*tmp_name;

	if (tmp)
	{
		tmp_name = ft_strndup(name, ft_strchr(name, '=') - name);
		update_var(tmp_name, ft_strchr(name, '=') + 1);
		free(tmp_name);
	}
	else
		add_var(name, ENV_VAR);
}

static void	execute_export(char *name)
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
		update_var_with_equal(tmp, name);
		return ;
	}
	if (tmp)
		tmp->scope = ENV_VAR;
	else
		add_var(name, EXPORT_VAR);
}

void	ft_export(char **cmds)
{
	g_mini.exit_status = 0;
	if (!cmds[1])
	{
		print_sorted_env();
		return ;
	}
	cmds++;
	while (*cmds)
	{
		execute_export(*cmds);
		cmds++;
	}
}
