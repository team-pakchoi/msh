/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:58:27 by sarchoi           #+#    #+#             */
/*   Updated: 2022/05/11 11:58:28 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_executable(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == -1)
		return (FT_FALSE);
	if (buf.st_mode & S_IFREG)
		return (FT_TRUE);
	print_error(path, "Not a file");
	g_mini.exit_status = 1;
	return (FT_FALSE);
}

int	valid_execute_permission(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == -1)
		return (FT_FALSE);
	if (buf.st_mode & S_IXUSR || buf.st_mode & S_IXGRP
		|| buf.st_mode & S_IXOTH)
		return (FT_TRUE);
	print_error2("cd", path, "Permission denied");
	g_mini.exit_status = 1;
	return (FT_FALSE);
}
