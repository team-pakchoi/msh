/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 00:09:09 by cpak              #+#    #+#             */
/*   Updated: 2022/04/25 00:09:10 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char    *set_prompt(int quote)
{
    char    *line;

    line = 0;
    if (quote == 0)
        line = readline(" ");
    else if (quote == '\'')
        line = readline(PROMPT_QUOTE);
    else if (quote == '"')
        line = readline(PROMPT_QUOTE_D);
    return (line);
}

void    check_str_quote_closed(char *str, int *quote)
{
    while (*str)
    {
        set_quotes_flag(*str, quote);
        str += 1;
    }
}

int deal_prompt(char **input)
{
    int quote;

    quote = 0;
	*input = readline(" ");
	if (*input == 0)
        return (0);
    check_str_quote_closed(*input, &quote);
    if (quote)
    {
        // unclosed quote
    }
    return (1);
}
