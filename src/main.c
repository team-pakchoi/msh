/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:26:36 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/11 15:20:03 by sarchoi          ###   ########seoul.kr  */
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
	init_env(envp);
	init_history(&his_fd, &prev_input);
	init_signal();
	while(1)
	{
		input = readline("prompt : ");
		if (!input)
            return (0);
        deal_command(input, envp);
        save_history(his_fd, input, &prev_input);
        free(input);
    }
    free(prev_input);
    free_global();
	return(EXIT_SUCCESS);
}
