/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_all_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 05:38:27 by cpak              #+#    #+#             */
/*   Updated: 2022/04/28 06:59:33 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*change_str(char *str, char *str_tar, char *str_src)
{
	char	*new;
	int		len_tar;
	int		len_src;
	int		i;

	i = 0;
	len_tar = ft_strlen(str_tar);
	len_src = ft_strlen(str_src);
	new = (char *)ft_calloc(
			ft_strlen(str) - len_tar + len_src + 1, sizeof(char));
	if (!new)
		return (0);
	while (ft_strncmp(str + i, str_tar, len_tar) != 0)
	{
		new[i] = str[i];
		i += 1;
	}
	i += ft_strlcpy(new + i, str_src, len_src + 1);
	i += ft_strlcpy(new + i, str + i - len_src + len_tar,
			ft_strlen(str + i - len_src + len_tar) + 1);
	free(str);
	return (new);
}

char	*trans_env_name_to_value(char *str, int start, int end, int *idx)
{
	char	*env_name;
	char	*env_value;
	char	*parsed_str;

	env_name = ft_strndup(str + start, end - start);
	if (env_name[1] == '?')
		env_value = ft_itoa((int)g_mini.exit_status);
	else
		env_value = find_var_value(env_name + 1);
	parsed_str = change_str(str, env_name, env_value);
	*idx = start + ft_strlen(env_value);
	if (env_name[1] == '?')
		free(env_value);
	free(env_name);
	return (parsed_str);
}

int	get_next_env_point(char *str, int *start, int *end)
{
	int	i;

	i = 0;
	*start = -1;
	while (str[i])
	{
		if (str[i] == '$')
			*start = i;
		else if (*start != -1)
		{
			if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
			{
				if (i - *start == 1 && str[i] == '?')
					i += 1;
				*end = i;
				return (1);
			}
		}
		i += 1;
	}
	if (*start == -1)
		return (0);
	*end = i;
	return (1);
}

int	trans_all_env(char **str)
{
	int	start;
	int	end;
	int	idx;

	idx = 0;
	while (get_next_env_point(*str + idx, &start, &end))
	{
		*str = trans_env_name_to_value(*str + idx, start, end, &idx);
		if (*str == 0)
			return (0);
	}
	return (1);
}
