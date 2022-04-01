/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 13:18:46 by cpak              #+#    #+#             */
/*   Updated: 2022/01/28 15:44:05 by cpak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path_in_envp(char *envp[])
{
	int	idx;

	idx = 0;
	while (envp[idx] != 0)
	{
		if (ft_strnstr(envp[idx], "PATH=", 7) != 0)
			return (envp[idx]);
		idx++;
	}
	return (0);
}

char	*find_command_path(char *envp[], char *command)
{
	char	**paths;
	char	*path;
	int		i;	

	path = find_path_in_envp(envp);
	if (path == 0)
		return (0);
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin("/", command);
		if (i == 0)
			path = ft_strjoin(ft_strtrim(paths[i], "PATH="), path);
		else
			path = ft_strjoin(paths[i], path);
		free(paths[i]);
		if (access(path, X_OK) == 0)
			break ;
		i += 1;
	}
	return (path);
}
