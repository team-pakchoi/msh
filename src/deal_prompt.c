/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 00:09:09 by cpak              #+#    #+#             */
/*   Updated: 2022/04/28 05:44:45 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_str_quote_closed(char *str, int *quote)
{
	while (*str)
	{
		set_quotes_flag(*str, quote);
		str += 1;
	}
}

int	deal_prompt(void)
{
	int	quote;

	quote = 0;
	g_mini.prompt_input = readline(g_mini.prompt_str);
	if (g_mini.prompt_input == 0)
		return (0);
	check_str_quote_closed(g_mini.prompt_input, &quote);
	if (quote)
		printf("unclosed quote\n");
	return (1);
}
