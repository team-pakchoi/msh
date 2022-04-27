/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:54:44 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/27 16:01:58 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	increase_shlvl(void)
{
	int	prev_value;
	char	*value;

	prev_value = ft_atoi(getenv("SHLVL"));
	value = ft_itoa(prev_value + 1);
	update_var("SHLVL", value);
	free(value);
}

void	init_env(char **envp)
{
	add_var(*envp, ENV_VAR);
	envp++;
	while (*envp)
	{
		add_var(*envp, ENV_VAR);
		envp++;
	}
	increase_shlvl();
	remove_var("OLDPWD");
}

void	ft_env(void)
{
	t_var	*tmp;

	tmp = g_mini.env;
	while (tmp)
	{
		if (tmp->scope == ENV_VAR)
			printf("%s\n", (char *)tmp->var);
		tmp = tmp->next;
	}
	g_mini.exit_status = 0;
}
