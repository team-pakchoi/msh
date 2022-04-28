/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:41:00 by cpak              #+#    #+#             */
/*   Updated: 2022/04/28 06:29:54 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_next_str(char *str, int *idx, int *sep)
{
	int	start;

	start = *idx;
	*sep = 0;
	if (str[*idx] == '"' || str[*idx] == '\'')
	{
		*sep = str[*idx];
		*idx += 1;
	}
	while (str[*idx])
	{
		if (*sep == str[*idx])
			return (ft_strndup(str + start, *idx - start + 1));
		else if (*sep == 0 && (str[*idx] == '"' || str[*idx] == '\''))
			return (ft_strndup(str + start, *idx - start));
		*idx += 1;
	}
	*sep = 0;
	return (ft_strndup(str + start, *idx - start));
}

int	parse_str_env(char **str)
{
	int		idx;
	char	*tar;
	char	*src;
	int		sep;

	idx = 0;
	sep = 0;
	while ((*str)[idx])
	{
		tar = get_next_str(*str, &idx, &sep);
		if (tar == 0)
			continue ;
		src = ft_strtrim(tar, (const char *)&sep);
		if (sep != '\'' && trans_all_env(&src) == 0)
			return (0);
		*str = change_str(*str, tar, src);
		idx -= ft_strlen(tar) - ft_strlen(src);
		if (sep != 0)
			idx += 1;
		free(src);
		free(tar);
	}
	return (1);
}

int	parse_cmd_env(char **cmd)
{
	int	idx;

	idx = 0;
	while (cmd[idx])
	{
		parse_str_env(&cmd[idx]);
		idx += 1;
	}
	return (1);
}
