/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 04:58:58 by cpak              #+#    #+#             */
/*   Updated: 2022/05/05 17:34:29 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_prompt_to_heredoc(char *delimiter)
{
	int		fd;
	char	*str;

	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("no such file or directory");
		g_mini.exit_status = 127;
	}
	while (1)
	{
		str = readline(PROMPT_HEREDOC);
		if (str == 0)
			break ;
		if (ft_strcmp(str, delimiter) == 0)
			break ;
		if (parse_str(&str) == -1)
			break ;
		ft_putstr_fd(str, fd);
		ft_putstr_fd("\n", fd);
		free(str);
		str = 0;
	}
	free(str);
	close(fd);
}

void	exec_heredoc(char *command[], int out_fd)
{
	restore_ori_stdin();
	restore_ori_stdout();
	write_prompt_to_heredoc(command[0]);
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
	print_file(".heredoc");
	unlink(".heredoc");
	return ;
}
