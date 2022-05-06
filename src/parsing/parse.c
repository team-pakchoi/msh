/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:41:00 by cpak              #+#    #+#             */
/*   Updated: 2022/05/05 22:33:33 by cpak             ###   ########seoul.kr  */
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

static void	remove_str_quotes(char **str)
{
	int		j;
	char	*tar;
	char	*new;
	int		sep;

	j = 0;
	while ((*str)[j])
	{
		tar = get_next_str((*str), &j, &sep);
		new = ft_strtrim(tar, (const char *)&sep);
		*str = change_str((*str), tar, new, j);
		j += ft_strlen(new);
		free(new);
		free(tar);
	}
}

int	parse_quotes(char **str)
{
	char	**strarr;
	int		i;

	strarr = split_with_quote((*str), is_white_space);
	i = 0;
	while (strarr[i])
	{
		remove_str_quotes(&strarr[i]);
		i += 1;
	}
	free(*str);
	*str = ft_strarr_to_str(strarr, " ");
	ft_free_arr(strarr);
	return (1);
}

int	parse_str(char **str)
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
		new = ft_strdup(tar);
		if (ft_strlen(new) == 1 && new[0] == '$' && is_quote((*str)[idx + 1]))
			new[0] = 0;
		if (sep != '\'' && trans_all_env(&new) == 0)
			return (-1);
		*str = change_str(*str, tar, new, idx);
		idx += ft_strlen(new);
		free(new);
		free(tar);
	}
	parse_quotes(&(*str));
	return (sep);
}

int	parse_cmd(char ***strarr)
{
	int	idx;
	int	sep;
	int	arr_len;

	idx = 0;
	arr_len = ft_strarr_len(*strarr);
	while ((*strarr)[idx])
	{
		sep = parse_str(&(*strarr)[idx]);
		if (ft_strlen((*strarr)[idx]) == 0 && sep == 0)
		{
			ft_strarr_remove(strarr, arr_len, idx);
			arr_len -= 1;
		}
		else
			idx += 1;
	}
	return (1);
}
