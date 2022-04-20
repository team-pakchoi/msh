/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:26:36 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/13 21:27:51 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_global()
{
	remove_var_list();
    remove_cmd_list();
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
		if (deal_prompt(&input) == 0)
		{
			printf("\033[1A");
			printf(PROMPT_STRING);
			printf("exit\n");
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
