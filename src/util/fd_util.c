/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_funcs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:22:24 by cpak              #+#    #+#             */
/*   Updated: 2022/03/31 15:06:22 by cpak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	keep_ori_std()
{
	dup2(STDIN_FILENO, 3);
	dup2(STDOUT_FILENO, 4);
}

void	restore_ori_stdin()
{
	dup2(3, STDIN_FILENO);
}

void	restore_ori_stdout()
{
	dup2(4, STDOUT_FILENO);
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

void    read_fd(int fd)
{
    char    *line;

    while (get_next_line(fd, &line) > 0)
    {
        printf("%s\n", line);
        free(line);
        line = 0;
    }
    printf("\n");
}
