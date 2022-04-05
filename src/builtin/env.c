/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:54:44 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/05 15:41:26 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	increase_shlvl()
{
	int	prev_value;

	prev_value = ft_atoi(getenv("SHLVL"));
	update_var("SHLVL", ft_itoa(prev_value + 1));
}

void	init_env(char **envp)
{
	add_var(ft_strdup(*envp), ENV_VAR);
	envp++;
	while (*envp)
	{
		add_var(ft_strdup(*envp), ENV_VAR);
		envp++;
	}
	increase_shlvl();
}

void	ft_env()
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
