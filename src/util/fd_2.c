/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 03:40:47 by cpak              #+#    #+#             */
/*   Updated: 2022/05/09 16:11:28 by cpak             ###   ########seoul.kr  */
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
	}
	free(line);
}

int	print_file(char *path)
{
	int	file_fd;

	file_fd = open(path, O_RDONLY);
	if (file_fd == -1)
	{
		perror("minishell: file error");
		g_mini.exit_status = 1;
		return (0);
	}
	read_fd(STDIN_FILENO);
	read_fd(file_fd);
	close(file_fd);
	return (1);
}
