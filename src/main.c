/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:26:36 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/03 13:54:30 by sarchoi          ###   ########seoul.kr  */
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
	char	*str;
	int		his_fd;

	(void)argc;
	(void)argv;
	init_env(envp);
	init_history(&his_fd);
	while(1)
	{
		str = readline("prompt : ");
		if (!str)
            return (0);
        deal_command(str, envp);
        save_history(str, his_fd);
        free(str);
    }
    free_global();
	return(EXIT_SUCCESS);
}