
#include "minishell.h"

char    *set_prompt(int quote)
{
    char    *line;

    if (quote == 0)
        line = readline(PROMPT_STRING);
    else if (quote == '\'')
        line = readline(PROMPT_QUOTE);
    else if (quote == '"')
        line = readline(PROMPT_QUOTE_D);
    return (line);
}

void check_quote_is_closed(char *str, int *quote)
{
    while (*str)
    {
        set_quotes_flag(*str, quote);
        str += 1;
    }
}

int deal_prompt(char **input, int quote)
{
    char    *str;
    char    *joined;

	str = set_prompt(quote);
	if (str == 0)
        return (1);
    joined = ft_strjoin(*input, str);
    if (**input)
        free(*input);
    *input = joined;
    check_quote_is_closed(str, &quote);
    free(str);
    if (quote)
    {
        joined = ft_strjoin(*input, "\n");
        free(*input);
        *input = joined;
        quote = deal_prompt(input, quote);
    }
    return (quote);
}