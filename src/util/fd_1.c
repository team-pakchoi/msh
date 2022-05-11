/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:22:24 by cpak              #+#    #+#             */
/*   Updated: 2022/05/11 13:10:45 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_fd_to_stdin(int fd)
{
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	set_pipein_to_stdout(int *fds)
{
	dup2(fds[1], STDOUT_FILENO);
	close(fds[0]);
	close(fds[1]);
}

void	set_pipeout_to_stdin(int *fds)
{
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
	close(fds[1]);
}

void	set_fileout_to_fd(char *path, int fd)
{
	int	file_fd;

	if (access(path, R_OK) == 0)
	{
		file_fd = open(path, O_RDONLY, 0644);
		dup2(file_fd, fd);
		close(file_fd);
	}
}

void	set_filein_to_fd(char *path, int fd)
{
	int	file_fd;

	if (access(path, W_OK) == 0)
	{
		file_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(file_fd, fd);
		close(file_fd);
		return ;
	}
	exit (1);
}
