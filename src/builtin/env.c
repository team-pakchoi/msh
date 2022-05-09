/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:54:44 by sarchoi           #+#    #+#             */
/*   Updated: 2022/05/03 18:24:03 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	increase_shlvl(void)
{
	int		prev_value;
	char	*value;

	prev_value = ft_atoi(getenv("SHLVL"));
	value = ft_itoa(prev_value + 1);
	update_var("SHLVL", value);
	free(value);
}

static void	update_shell(char **argv)
{
	char	*cwd;
	char	*tmp;
	char	*tmp2;

	if (argv[0][0] == '/')
	{
		update_var("SHELL", argv[0]);
		return ;
	}
	cwd = getcwd(NULL, 0);
	if (ft_strncmp(argv[0], "./", 2) == 0)
	{
		tmp = ft_strjoin(cwd, argv[0] + 1);
		update_var("SHELL", tmp);
		free(tmp);
		free(cwd);
		return ;
	}
	tmp = ft_strjoin(cwd, "/");
	tmp2 = ft_strjoin(tmp, argv[0]);
	update_var("SHELL", tmp2);
	free(tmp);
	free(tmp2);
	free(cwd);
}

void	init_env(int argc, char **argv, char **envp)
{
	(void)argc;
	add_var(*envp, ENV_VAR);
	envp++;
	while (*envp)
	{
		add_var(*envp, ENV_VAR);
		envp++;
	}
	increase_shlvl();
	update_shell(argv);
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
