/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 04:41:40 by cpak              #+#    #+#             */
/*   Updated: 2022/05/11 16:39:41 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_assign_cmd(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		while (cmd[i][j])
		{
			if (!ft_isalpha(cmd[i][j]) && !ft_isdigit(cmd[i][j])
					&& cmd[i][j] != '_')
				break ;
			j += 1;
		}
		if (cmd[i][j] != '=')
			break ;
		i += 1;
	}
	return (i);
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

	idx = is_assign_cmd(command);
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
