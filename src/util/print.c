/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 20:42:50 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/30 02:52:26 by cpak             ###   ########seoul.kr  */
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

void	print_prompt(void)
{
	char	*cwd;
	char	*home_dir;

	cwd = getcwd(NULL, 0);
	home_dir = find_var_value("HOME");
	ft_putstr_fd(PROMPT_COLOR_PWD, 1);
	if (home_dir != NULL && ft_strncmp(cwd, home_dir, ft_strlen(home_dir)) == 0)
	{
		ft_putstr_fd("~", 1);
		ft_putstr_fd(cwd + ft_strlen(home_dir), 1);
	}
	else
		ft_putstr_fd(cwd, 1);
	ft_putstr_fd(PROMPT_COLOR_PROMPT, 1);
	ft_putstr_fd(PROMPT_STRING, 1);
	ft_putstr_fd(PROMPT_COLOR_RESET, 1);
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
