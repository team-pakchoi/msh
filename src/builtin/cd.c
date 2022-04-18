/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:32:11 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/16 21:06:30 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_directory(struct stat *buf)
{
	if (buf->st_mode & S_IFDIR)
		return (FT_TRUE);
	return (FT_FALSE);
}

static int	has_permission(struct stat *buf)
{
	if (buf->st_mode & S_IRUSR)
		return (FT_TRUE);
	return (FT_FALSE);
}

static int	has_directory(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == -1)
		return (FT_FALSE);
	if (is_directory(&buf) == FT_TRUE)
		return (FT_TRUE);
	return (FT_FALSE);
}

static void	print_directory(void)
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

int	ft_chdir(char *path)
{
	struct stat	buf;
	char	*cwd;

	if (stat(path, &buf) != 0)
	{
		print_error2("cd", path, "No such file or directory");
		g_mini.exit_status = 1;
		return (FT_ERROR);
	}
	if (!is_directory(&buf))
	{
		print_error2("cd", path, "Not a directory");
		g_mini.exit_status = 1;
		return (FT_ERROR);
	}
	if (!has_permission(&buf))
	{
		print_error2("cd", path, "Permission denied");
		g_mini.exit_status = 1;
		return (FT_ERROR);
	}
	if (chdir(path) == FT_ERROR)
	{
		print_strerror("cd");
		g_mini.exit_status = 1;
		return (FT_ERROR);
	}
	cwd = getcwd(NULL, 0);
	if (find_var_value("OLDPWD") == NULL)
		add_var(ft_strjoin("OLDPWD=", find_var_value("PWD")), ENV_VAR);
	else
		update_var("OLDPWD", find_var_value("PWD"));
	update_var("PWD", cwd);
	free(cwd);
	return (FT_SUCCESS);
}

void	ft_cd(char **cmds)
{
	char	*oldpwd;
	char	**paths;
	char	*path;

	if (ft_strcmp(cmds[1], "-") == 0)
	{
		oldpwd = find_var_value("OLDPWD");
		if (oldpwd == NULL)
		{
			print_error("cd", "OLDPWD not set");
			g_mini.exit_status = 1;
			return ;
		}
		if (ft_chdir(oldpwd) == FT_ERROR)
			return ;
		print_directory();
		return ;
	}
	if (ft_strcmp(cmds[1], "~") == 0)
	{
		path = ft_strjoin(find_var_value("HOME"), "/");
		ft_chdir(path);
		return ;
	}
	if (cmds[1][0] == '/')
	{
		ft_chdir(cmds[1]);
		return;
	}
	if (find_var_value("CDPATH") != NULL)
	{
		paths = ft_split(find_var_value("CDPATH"), ':');
		while (*paths)
		{
			path = ft_strjoin(*paths, "/");
			path = ft_strjoin(path, cmds[1]);
			if (has_directory(path) == FT_TRUE)
			{
				if (ft_chdir(path) == FT_ERROR)
					return ;
				print_directory();
				return ;
			}
			free(path);
			paths++;
		}
	}
	if (ft_chdir(cmds[1]) == FT_ERROR)
		return ;
}
