/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   welcome.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 13:58:07 by sarchoi           #+#    #+#             */
/*   Updated: 2022/05/11 14:20:58 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_welcome(void)
{
	int		file;
	char	buf[1];
	int		len;
	int		line;

	file = open("../welcome.txt", O_RDONLY);
	if (file == -1)
		return ;
	ft_putstr_fd("\033[01;35m", 1);
	line = 1;
	while (1)
	{
		len = read(file, buf, 1);
		if (len == 0)
			break ;
		if (line == 150)
			ft_putstr_fd("\033[01;32m", 1);
		else if (line == 280)
			ft_putstr_fd("\033[01;30m", 1);
		write(STDOUT_FILENO, buf, len);
		line++;
	}
	ft_putstr_fd("\033[0m", 1);
	close(file);
}
