/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 01:00:21 by cpak              #+#    #+#             */
/*   Updated: 2022/05/09 01:19:18 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_op_len(char *str)
{
	int		len;
	char	c;

	len = 0;
	c = str[len];
	while (c)
	{
		if (c != '|' && c != '<' && c != '>')
			break ;
		len += 1;
		c = str[len];
	}
	return (len);
}

int	is_op(char *str, int *sep_num)
{
	int	len;

	len = get_op_len(str);
	if (len == 0)
		*sep_num = 0;
	else if (!ft_strncmp(str, "|", len))
		*sep_num = 1;
	else if (!ft_strncmp(str, "<", len))
		*sep_num = 2;
	else if (!ft_strncmp(str, "<<", len))
		*sep_num = 3;
	else if (!ft_strncmp(str, ">", len))
		*sep_num = 4;
	else if (!ft_strncmp(str, ">>", len))
		*sep_num = 5;
	else
	{
		*sep_num = -1;
		g_mini.exit_status = (unsigned char)95;
		return (0);
	}
	return (len);
}

int	is_white_space(char *str, int *sep_num)
{
	if (*str == 32)
		*sep_num = 1;
	else
		*sep_num = 0;
	return (*sep_num);
}
