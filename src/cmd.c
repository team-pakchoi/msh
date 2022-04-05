#include "minishell.h"

void set_quotes_flag(char c, int *flag)
{
    if (c == 34 || c == 39)
    {
        if (*flag != 0)
            *flag = 0;
        else
            *flag = c;
    }
}

int get_is_op(char *str)
{
    if (*str == '|')
        return (1);
    if (*str == '>')
    {
        str += 1;
        if (*str == '>')
            return (3);
        if (*str == '<')
            return (-1);    // error
        return (2);
    }
    if (*str == '<')
    {
        str += 1;
        if (*str == '<')
            return (5);
        if (*str == '>')
            return (-1);    // error
        return (4);
    }
    return (0);
}

int get_len_to_next(char *str)
{
    int len;
    int flag;
    int has_op;

    len = 0;
    flag = 0;
    has_op = 0;
    while (str[len])
    {
        if (flag == 0)
        {
            has_op = get_is_op(str + len);
            if (has_op != 0)
                break ;
        }
        set_quotes_flag(str[len], &flag);
        len += 1;
    }
    return (len + 1);
}

char    *get_str_command(char *str, int len)
{
    char    *result;

    result = (char *)malloc(sizeof(char) * (len + 1));
    if (!result)
        return (0);
    result[len] = 0;
    ft_strlcpy(result, str, len);
    return (result);
}

int parse_command(char *str)
{
    char    *cmd;
    int     len;
    int     op;

    op = 1;
    while (*str)
    {
        len = get_len_to_next(str);
        cmd = get_str_command(str, len);
        if (!cmd)
            return (0);
        if (add_cmd(cmd, op) == 0)
            return (0);
        str += len;
        op = get_is_op(str - 1);
        if (op == 3 || op == 5)
            str += 2;
        else
            str += 1;
        cmd = 0;
        len = 0;
    }
    return (1);
}