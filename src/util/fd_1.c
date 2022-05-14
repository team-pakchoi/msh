/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:22:24 by cpak              #+#    #+#             */
/*   Updated: 2022/05/11 15:03:42 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_fd_to_stdin(int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
		return (0);
	close(fd);
	return (1);
}

int	set_pipein_to_stdout(int *fds)
{
	if (dup2(fds[1], STDOUT_FILENO) == -1)
		return (0);
	close(fds[0]);
	close(fds[1]);
	return (1);
}

int	set_pipeout_to_stdin(int *fds)
{
	if (dup2(fds[0], STDIN_FILENO) == -1)
		return (0);
	close(fds[0]);
	close(fds[1]);
	return (1);
}

int	set_fileout_to_fd(char *path, int fd)
{
	int	file_fd;

	if (access(path, R_OK) == 0)
	{
		file_fd = open(path, O_RDONLY, 0644);
		if (file_fd == -1)
			return (0);
		if (dup2(file_fd, fd) == -1)
			return (0);
		close(file_fd);
	}
	return (1);
}

int	set_filein_to_fd(char *path, int fd)
{
	int	file_fd;

	if (access(path, W_OK) == 0)
	{
		file_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file_fd == -1)
			return (0);
		if (dup2(file_fd, fd) == -1)
			return (0);
		close(file_fd);
		return (1);
	}
	exit (1);
}
