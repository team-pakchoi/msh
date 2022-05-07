/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 00:09:03 by cpak              #+#    #+#             */
/*   Updated: 2022/05/06 15:53:34 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(char **cmd)
{
	if (!ft_strcmp(*cmd, "cd"))
		return (1);
	if (!ft_strcmp(*cmd, "echo"))
		return (2);
	if (!ft_strcmp(*cmd, "env"))
		return (3);
	if (!ft_strcmp(*cmd, "exit"))
		return (4);
	if (!ft_strcmp(*cmd, "export"))
		return (5);
	if (!ft_strcmp(*cmd, "pwd"))
		return (6);
	if (!ft_strcmp(*cmd, "unset"))
		return (7);
	return (0);
}

static void	route_builtin(char **cmd, int n)
{
	if (n == 1)
		return (ft_cd(cmd));
	if (n == 2)
		return (ft_echo(cmd));
	if (n == 3)
		return (ft_env());
	if (n == 4)
		return (ft_exit(cmd));
	if (n == 5)
		return (ft_export(cmd));
	if (n == 6)
		return (ft_pwd());
	if (n == 7)
		return (ft_unset(cmd));
}

int	exec_builtin(char **cmd)
{
	int	n;

	n = is_builtin(cmd);
	if (n)
	{
		if (g_mini.cmd_len != g_mini.cmd_idx)
			set_self_pipe();
		route_builtin(cmd, n);
		restore_ori_stdout();
	}
	return (n);
}

static char	*find_cmd_path(char *command)
{
	char	**paths;
	char	*path;
	int		i;

	path = find_var_value("PATH");
	if (path == 0)
		return (0);
	paths = ft_split(path, ':');
	i = 0;
	if (ft_strnstr(command, "/", ft_strlen(command)) && !access(command, X_OK))
		return (command);
	while (paths[i])
	{
		path = ft_strjoin("/", command);
		if (i == 0)
			path = ft_strjoin(ft_strtrim(paths[i], "PATH="), path);
		else
			path = ft_strjoin(paths[i], path);
		free(paths[i]);
		if (access(path, X_OK) == 0)
			break ;
		i += 1;
	}
	return (path);
}

int	exec_execve(char **command)
{
	pid_t	pid;
	int		fds[2];
	int		status;

	pipe(fds);
	pid = fork();
	if (pid == 0)
	{
		if (g_mini.cmd_len != g_mini.cmd_idx)
			set_pipein_to_stdout(fds);
		if (**command == 0)
			return (0);
		if (execve(find_cmd_path(command[0]), command, find_all_env()) == -1)
		{
			print_error(command[0], "command not found");
			exit (127);
		}
		return (0);
	}
	if (g_mini.cmd_len != g_mini.cmd_idx)
		set_pipeout_to_stdin(fds);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_mini.exit_status = WEXITSTATUS(status);
	return (1);
}
