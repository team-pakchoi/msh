/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 19:31:52 by cpak              #+#    #+#             */
/*   Updated: 2022/04/01 19:32:01 by cpak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipex(int idx, char *envp[])
{
	pid_t	pid;
	int		fds[2];
	int		status;

	pipe(fds);
	pid = fork();
	if (pid == 0 && idx > 0)
	{
		set_pipein_to_stdout(fds);
		pipex(idx - 1, envp);
        exit(0);
	}
	else if (pid != 0)
	{
		set_pipeout_to_stdin(fds);
		waitpid(pid, &status, 0);
		g_mini.exit_status = status;
		execute_nth_cmd(idx, envp);
	}
}
