/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 03:53:42 by sarchoi           #+#    #+#             */
/*   Updated: 2022/05/09 15:41:24 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_execve(char *cmd, char **cmds)
{
	struct stat	buf;

	if (stat(cmd, &buf) != 0)
	{
		if (find_var_value("PATH") == NULL)
			print_error(cmds[0], "No such file or directory");
		else
			print_error(cmds[0], "command not found");
		g_mini.exit_status = 127;
		return (FT_ERROR);
	}
	if (!(buf.st_mode & S_IXUSR || buf.st_mode & S_IXGRP
			|| buf.st_mode & S_IXOTH))
	{
		print_error(cmds[0], "Permission denied");
		g_mini.exit_status = 126;
		return (FT_ERROR);
	}
	if (execve(cmd, cmds, find_all_env()) == FT_ERROR)
	{
		print_error(cmds[0], "command not found");
		g_mini.exit_status = 127;
		return (FT_ERROR);
	}
	return (FT_SUCCESS);
}

static int	execve_with_path(char **cmds)
{
	char	**paths;
	char	**paths_start;
	char	*cmd;
	char	*tmp;

	paths = ft_split(find_var_value("PATH"), ':');
	paths_start = paths;
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		cmd = ft_strjoin(tmp, cmds[0]);
		free(tmp);
		if (has_directory(*paths) && valid_executable(cmd)
			&& ft_execve(cmd, cmds))
		{
			free(cmd);
			ft_split_free(paths_start);
			return (FT_TRUE);
		}
		free(cmd);
		paths++;
	}
	ft_split_free(paths_start);
	return (FT_FALSE);
}

static void	run_command(char **cmds)
{
	if (cmds[0][0] == '/')
	{
		if (ft_execve(cmds[0], cmds))
			return ;
	}
	if (cmds[0][0] != '.' && find_var_value("PATH") != NULL)
	{
		if (execve_with_path(cmds))
			return ;
	}
	ft_execve(cmds[0], cmds);
}

static void	set_exit_status(int status)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 1);
		g_mini.exit_status = 131;
	}
	if (WIFEXITED(status))
		g_mini.exit_status = WEXITSTATUS(status);
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
		signal(SIGQUIT, SIG_DFL);
		if (g_mini.cmd_len != g_mini.cmd_idx)
			set_pipein_to_stdout(fds);
		if (**command == 0)
			return (0);
		run_command(command);
		if (g_mini.exit_status != 0)
			exit (g_mini.exit_status);
		return (0);
	}
	if (g_mini.cmd_len != g_mini.cmd_idx)
		set_pipeout_to_stdin(fds);
	waitpid(pid, &status, 0);
	set_exit_status(status);
	return (1);
}
