/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:26:36 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/27 15:10:09 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_global(void)
{
	remove_var_list();
	remove_cmd_list();
	free(g_mini.prompt_str);
	free(g_mini.history.prev_input);
}

void	update_prompt_str(void)
{
	char	*cwd;
	char	*home;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	home = find_var_value("HOME");
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		tmp = cwd;
		cwd = ft_strjoin("~", cwd + ft_strlen(home));
		free(tmp);
	}
	tmp = g_mini.prompt_str;
	g_mini.prompt_str = ft_strjoin(PROMPT_COLOR_PWD, cwd);
	free(tmp);
	free(cwd);
	tmp = g_mini.prompt_str;
	g_mini.prompt_str = ft_strjoin(g_mini.prompt_str, PROMPT_COLOR_PROMPT);
	free(tmp);
	tmp = g_mini.prompt_str;
	g_mini.prompt_str = ft_strjoin(g_mini.prompt_str, PROMPT_STRING);
	free(tmp);
	tmp = g_mini.prompt_str;
	g_mini.prompt_str = ft_strjoin(g_mini.prompt_str, PROMPT_COLOR_RESET);
	free(tmp);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	keep_ori_std();
	init_env(envp);
	init_history();
	init_signal();
	while (1)
	{
		update_prompt_str();
		if (deal_prompt() == 0)
		{
			eof_handler();
			free_global();
			return (g_mini.exit_status);
		}
		save_history();
		deal_command();
		remove_cmd_list();
		restore_ori_stdin();
		free(g_mini.prompt_input);
		g_mini.prompt_input = 0;
		g_mini.cmd_idx = 1;
	}
	free_global();
	return(EXIT_SUCCESS);
}
