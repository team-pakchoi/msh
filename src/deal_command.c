/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:39:03 by cpak              #+#    #+#             */
/*   Updated: 2022/04/06 14:39:04 by cpak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int deal_command(char *str, char *envp[])
{
    pid_t   pid;
    int     status;
    int     fds[2];

    pipe(fds);
    pid = fork();
    if (pid == 0)
    {
        g_mini.cmd_len = 0;
        if (set_cmd_list(str) == 0)
            exit(0);
        read_all_cmd();
        pipex(g_mini.cmd_len - 1, envp);
        exit(0);
    }
    else
        waitpid(pid, &status, 0);
    return (1);
}
