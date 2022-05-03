/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 03:40:47 by cpak              #+#    #+#             */
/*   Updated: 2022/05/03 18:03:02 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	keep_ori_std(void)
{
	dup2(STDIN_FILENO, 3);
	dup2(STDOUT_FILENO, 4);
}

void	restore_ori_stdin(void)
{
	dup2(3, STDIN_FILENO);
}

void	restore_ori_stdout(void)
{
	dup2(4, STDOUT_FILENO);
}

void	read_fd(int fd)
{
	char	*line;

	while (get_next_line(fd, &line) > 0)
	{
		printf("%s", line);
		free(line);
		line = 0;
	}
}

void	print_file(char *path)
{
	int	file_fd;

	file_fd = open(path, O_RDONLY);
	if (file_fd == -1)
	{
		perror("no such file or directory");
		g_mini.exit_status = 127;
	}
	read_fd(file_fd);
	close(file_fd);
}
