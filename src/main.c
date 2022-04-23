/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:26:36 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/24 02:51:10 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_global(void)
{
	remove_var_list();
	remove_cmd_list();
}

void	update_prompt_str(void)
{
	char	*cwd;
	char	*home;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	home = find_var_value("HOME");
	if (ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		tmp = cwd;
		cwd = ft_strjoin("~", cwd + ft_strlen(home));
		free(tmp);
	}
	g_mini.prompt_str = ft_strjoin(PROMPT_COLOR_PWD, cwd);
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
	char	*input;
    char    *prev_input;
	int		his_fd;

	(void)argc;
	(void)argv;
	keep_ori_std();
	init_env(envp);
	init_history(&his_fd, &prev_input);
	init_signal();
	while(1)
	{
		update_prompt_str();
		if (deal_prompt(&input) == 0)
		{
			ft_putstr_fd("\033[1A", 1);
			ft_putstr_fd(g_mini.prompt_str, 1);
			ft_putstr_fd("exit\n", 1);
			free(prev_input);
			free_global();
			return (g_mini.exit_status);
		}
		save_history(his_fd, input, &prev_input);
		deal_command(input);
		remove_cmd_list();
		restore_ori_stdin();
		free(input);
		input = 0;
		g_mini.cmd_idx = 1;
    }
    free(prev_input);
    free_global();
	return(EXIT_SUCCESS);
}
