/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 01:00:21 by cpak              #+#    #+#             */
/*   Updated: 2022/04/28 02:58:17 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_op_input(char *str, int *sep_num, int *len)
{
	if (str[0] == '<')
	{
		*sep_num = 2;
		*len = 1;
		if (str[1] == '<')
		{
			*sep_num = 3;
			*len = 2;
		}
		else if (str[1] == '>')
		{
			*sep_num = -1;
			*len = 2;
			g_mini.exit_status = 1;
		}
	}
	return (1);
}

int	is_op_output(char *str, int *sep_num, int *len)
{
	if (str[0] == '>')
	{
		*sep_num = 4;
		*len = 1;
		if (str[1] == '>')
		{
			*sep_num = 5;
			*len = 2;
		}
		else if (str[1] == '<')
		{
			*sep_num = -1;
			*len = 2;
			g_mini.exit_status = 1;
		}
	}
	return (1);
}

int	is_op(char *str, int *sep_num)
{
	int	len;

	len = 0;
	*sep_num = 0;
	if (str[0] == '|')
	{
		*sep_num = 1;
		return (1);
	}
	if (is_op_input(str, sep_num, &len) && len != 0)
		return (len);
	if (is_op_output(str, sep_num, &len) && len != 0)
		return (len);
	return (0);
}

int	is_white_space(char *str, int *sep_num)
{
	if (*str == 32)
		*sep_num = 1;
	else
		*sep_num = 0;
	return (*sep_num);
}
