/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 04:58:58 by cpak              #+#    #+#             */
/*   Updated: 2022/05/11 16:39:18 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	open_error(void)
{
	perror("no such file or directory");
	g_mini.exit_status = 127;
}

void	write_prompt_to_heredoc(char *delimiter)
{
	int		fd;
	char	*str;

	fd = open(".heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		open_error();
	signal(SIGINT, sigint_heredoc_handler);
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

int	exec_heredoc(void)
{
	if (!print_file(".heredoc"))
		return (0);
	unlink(".heredoc");
	return (1);
}
