/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_var_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 15:23:33 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/02 15:35:45 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_shell_var(char *name_and_value)
{
	add_var(g_mini.shell_var, name_and_value);
}

char	*find_shell_var(char *name)
{
	return (find_var(g_mini.shell_var, name));
}

void	remove_shell_var(char	*name)
{
	remove_var(g_mini.shell_var, name);
}

void	update_shell_var(char *name, char *new_value)
{
	update_var(g_mini.shell_var, name, new_value);
}
