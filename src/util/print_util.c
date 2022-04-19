/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 20:42:50 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/19 15:25:33 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_strerror(char *cmd_str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
}

void	print_error(char *cmd_str, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
}

void	print_error2(char *cmd_str, char *arg_str, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(arg_str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
}

void	print_cwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		print_strerror("cd");
		return ;
	}
	printf("%s\n", cwd);
	free(cwd);
}
