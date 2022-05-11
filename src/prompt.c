/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 00:09:09 by cpak              #+#    #+#             */
/*   Updated: 2022/05/11 14:31:50 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	deal_prompt(void)
{
	g_mini.prompt_input = readline(g_mini.prompt_str);
	if (g_mini.prompt_input == 0)
		return (0);
	return (1);
}
