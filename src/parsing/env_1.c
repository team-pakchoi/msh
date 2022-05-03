/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:41:00 by cpak              #+#    #+#             */
/*   Updated: 2022/05/03 14:33:29 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_next_str(char *str, int *idx, int *sep)
{
	int	len;

	*sep = 0;
	len = 0;
	set_quotes_flag(str[*idx], sep);
	if (*sep != 0)
	{
		len = check_quote_closed(str + (*idx), sep);
		set_quotes_flag(str[*idx], sep);
		if (len)
			return (ft_strndup(str + (*idx), len + 1));
	}
	len += 1;
	while (str[*idx + len] && !is_quote(str[*idx + len]))
		len += 1;
	*sep = 0;
	return (ft_strndup(str + (*idx), len));
}

int	parse_str_env(char **str)
{
	int		idx;
	char	*tar;
	char	*new;
	int		sep;

	idx = 0;
	sep = 0;
	while ((*str)[idx])
	{
		tar = get_next_str(*str, &idx, &sep);
		if (tar == 0)
			continue ;
		new = ft_strtrim(tar, (const char *)&sep);
		if (sep != '\'' && trans_all_env(&new) == 0)
			return (-1);
		*str = change_str(*str, tar, new);
		idx += ft_strlen(new);
		free(new);
		free(tar);
	}
	return (sep);
}

int	parse_cmd_env(char ***strarr)
{
	int	idx;
	int	sep;
	int	arr_len;

	idx = 0;
	arr_len = ft_strarr_len(*strarr);
	while ((*strarr)[idx])
	{
		sep = parse_str_env(&(*strarr)[idx]);
		if (ft_strlen((*strarr)[idx]) == 0 && sep == 0 && idx != arr_len - 1)
		{
			ft_strarr_remove(strarr, idx);
			arr_len = ft_strarr_len(*strarr);
		}
		else
			idx += 1;
	}
	return (1);
}
