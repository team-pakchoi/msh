/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 04:41:40 by cpak              #+#    #+#             */
/*   Updated: 2022/04/30 01:38:32 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_assign_cmd(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx])
	{
		if (!ft_isalpha(str[idx]) && !ft_isdigit(str[idx]) && str[idx] != '_')
			break ;
		idx += 1;
	}
	return (str[idx] == '=');
}

static void	exec_set(char *name)
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

static void	set_var(char **cmds)
{
	g_mini.exit_status = 0;
	while (*cmds)
	{
		exec_set(*cmds);
		cmds++;
	}
}

int	exec_assign(char **command, t_cmd *cmd)
{
	int	idx;

	idx = 0;
	while (command[idx])
	{
		if (!is_assign_cmd(command[idx]))
			break ;
		idx += 1;
	}
	if (!command[idx])
	{
		if (cmd->prev && cmd->prev->op == 1)
			return (-1);
		if (cmd->next && cmd->next->op == 1)
			return (-1);
		set_var(command);
		set_self_pipe();
		restore_ori_stdout();
	}
	return (idx);
}
