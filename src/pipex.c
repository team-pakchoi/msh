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

int execute_command(char *cmd, char *envp[])
{
	char	**command;

	command = split_command(cmd, 32);
	if (access(command[0], X_OK) != 0)
		command[0] = find_command_path(envp, command[0]);
	if (execve(command[0], command, envp) == -1)
	{
		perror("command not found");
		exit (127);
	}
	return (1);
}

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
		execute_command(cmd[idx], envp);
	}
}
