/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:54:44 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/01 22:34:35 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	increase_shlvl()
{
	int	prev_value;

	prev_value = ft_atoi(getenv("SHLVL"));
	update_env("SHLVL", ft_itoa(prev_value + 1));
}

void	init_env(char **envp)
{
	t_list	*tmp;

	tmp = ft_lstnew(ft_strdup(*envp));
	envp++;
	g_mini.env = tmp;
	while (*envp)
	{
		tmp = ft_lstnew(ft_strdup(*envp));
		ft_lstadd_back(&g_mini.env, tmp);
		envp++;
	}
	increase_shlvl();
}

int	ft_env()
{
	t_list	*tmp;

	tmp = g_mini.env;
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
	return (FT_SUCCESS);
}
