/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:22:27 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/19 15:29:03 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_directory(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == -1)
		return (FT_FALSE);
	if (buf.st_mode & S_IFDIR)
		return (FT_TRUE);
	print_error2("cd", path, "Not a directory");
	g_mini.exit_status = 1;
	return (FT_FALSE);
}

int	valid_permission(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == -1)
		return (FT_FALSE);
	if (buf.st_mode & S_IRUSR)
		return (FT_TRUE);
	print_error2("cd", path, "Permission denied");
	g_mini.exit_status = 1;
	return (FT_FALSE);
}

int	has_directory(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == -1)
		return (FT_FALSE);
	if (valid_directory(path) == FT_TRUE)
		return (FT_TRUE);
	return (FT_FALSE);
}
