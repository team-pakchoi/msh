/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_len_to_next.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 07:24:50 by cpak              #+#    #+#             */
/*   Updated: 2022/04/29 18:20:46 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

void	set_quotes_flag(char c, int *flag)
{
	if (is_quote(c))
	{
		if (*flag == c)
			*flag = 0;
		else if (*flag == 0)
			*flag = c;
	}
}

int	check_quote_closed(char *str, int *flag)
{
	int	len;

	len = 0;
	while (str[len] && *flag != 0)
	{
		len += 1;
		set_quotes_flag(str[len], flag);
		if (*flag == 0)
			return (len);
	}
	return (0);
}

void	deal_sep_func(char **str, int (*sep_func)(char *, int *))
{
	int	sep_len;
	int	sep;

	sep = 0;
	while (**str)
	{
		sep_len = sep_func(*str, &sep);
		if (sep_len == 0)
			break ;
		*str += sep_len;
	}
}

int	get_len_to_next(char **str, int (*sep_func)(char *, int *))
{
	int	len;
	int	flag;
	int	sep;
	int	sep_len;

	len = 0;
	flag = 0;
	sep = 0;
	deal_sep_func(str, sep_func);
	while ((*str)[len])
	{
		set_quotes_flag((*str)[len], &flag);
		if (flag != 0)
			len += check_quote_closed(*str + len, &flag);
		sep_len = sep_func(*str + len, &sep);
		if (sep_len != 0)
			break ;
		len += sep_len + 1;
	}
	return (len);
}
