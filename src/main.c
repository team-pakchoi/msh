/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:26:36 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/02 14:05:55 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    read_all_cmd()
{
    t_cmd   *node;
    int     len;

    node = g_mini.cmd;
    len = g_mini.cmd_len;
    while (len > 0)
    {
        write(2, "str: ", 5);
        write(2, node->str, ft_strlen(node->str));
        write(2, ", op:", 5);
        write(2, ft_itoa(node->op), ft_strlen(ft_itoa(node->op)));
        write(2, "\n", 1);
        node = node->next;
        len -= 1;
    }
    write(2, "-----parsed-------\n", 19);
}

int deal_command(char *str, char *envp[]) {
    pid_t   pid;
    int     status;
    int     fds[2];

    pipe(fds);
    pid = fork();
    if (pid == 0)
    {
        g_mini.cmd_len = 0;
        if (parse_command(str) == 0)
            exit(0);
        read_all_cmd();
        pipex(g_mini.cmd_len - 1, envp);
        exit(0);
    }
    else
    {
        set_pipeout_to_stdin(fds);
        waitpid(pid, &status, 0);
        read_fd(STDIN_FILENO);
    }
    return (1);
}

static void	free_global()
{
	ft_lstclear(&g_mini.env, free);
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
	// while(1)
	// {
		str = readline("prompt : ");
		if (!str)
			return (0);
        deal_command(str, envp);
        save_history(str, his_fd);
        free(str);
    // }
    free_global();
	return(EXIT_SUCCESS);
}