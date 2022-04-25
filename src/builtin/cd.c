/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 13:32:11 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/25 15:53:06 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_chdir(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) != 0)
	{
		print_error2("cd", path, "No such file or directory");
		g_mini.exit_status = 1;
		return (FT_ERROR);
	}
	if (!valid_directory(path) || !valid_permission(path))
		return (FT_ERROR);
	if (chdir(path) == FT_ERROR)
	{
		print_strerror("cd");
		g_mini.exit_status = 1;
		return (FT_ERROR);
	}
	set_pwd_env();
	return (FT_SUCCESS);
}

static void	move_to_oldpwd(void)
{
	char	*oldpwd;

	oldpwd = find_var_value("OLDPWD");
	if (oldpwd == NULL)
	{
		print_error("cd", "OLDPWD not set");
		g_mini.exit_status = 1;
		return ;
	}
	if (ft_chdir(oldpwd) == FT_ERROR)
	{
		print_error("cd", "OLDPWD not set");
		g_mini.exit_status = 1;
		return ;
	}
	print_cwd();
}

static int	move_to_cdpath(char *path)
{
	char	**cdpaths;
	char	*tmp;

	cdpaths = ft_split(find_var_value("CDPATH"), ':');
	while (*cdpaths)
	{
		tmp = ft_strjoin(ft_strjoin(*cdpaths, "/"), path);
		if (has_directory(tmp) && ft_chdir(tmp))
		{
			print_cwd();
			free(tmp);
			return (FT_TRUE);
		}
		free(tmp);
		cdpaths++;
	}
	return (FT_FALSE);
}

static int	move_with_tilde(char *path)
{
	char	*tmp;

	if (find_var_value("HOME") == NULL)
	{
		print_error("cd", "HOME not set");
		g_mini.exit_status = 1;
		return (FT_ERROR);
	}
	tmp = ft_strjoin(find_var_value("HOME"), &path[1]);
	ft_chdir(tmp);
	free(tmp);
	return (FT_SUCCESS);
}

void	ft_cd(char **cmds)
{
	if ((!cmds[1] || ft_strcmp(cmds[1], "~") == 0) && find_var_value("HOME"))
		ft_chdir(ft_strjoin(find_var_value("HOME"), "/"));
	else if (ft_strcmp(cmds[1], "-") == 0)
		move_to_oldpwd();
	else
	{
		if (cmds[1][ft_strlen(cmds[1]) - 1] == '\\')
			cmds[1][ft_strlen(cmds[1]) - 1] = '\0';
		if (cmds[1][0] == '/')
		{
			ft_chdir(cmds[1]);
			return ;
		}
		if (cmds[1][0] == '~')
		{
			if (move_with_tilde(cmds[1]))
				return ;
		}
		if (cmds[1][0] != '.' && find_var_value("CDPATH") != NULL)
		{
			if (move_to_cdpath(cmds[1]))
				return ;
		}
		ft_chdir(cmds[1]);
	}
}
