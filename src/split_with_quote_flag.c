/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:38:47 by cpak              #+#    #+#             */
/*   Updated: 2022/04/06 14:38:53 by cpak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void set_quotes_flag(char c, int *flag)
{
    if (c == 34 || c == 39)
    {
        if (*flag == c)
            *flag = 0;
        else if (*flag == 0)
            *flag = c;
    }
}

int get_len_to_next(char **str, int (*sep_func)(char *, int *))
{
    int len;
    int flag;
    int sep;
    int sep_len;

    len = 0;
    flag = 0;
    sep = 0;
    while (**str)
    {
        sep_len = sep_func(*str, &sep);
        if (sep_len == 0)
            break ;
        *str += sep_len;
    }
    while ((*str)[len])
    {
        if (flag == 0)
        {
            sep_len = sep_func(*str + len, &sep);
            if (sep_len != 0)
                break ;
            len += sep_len;
        }
        set_quotes_flag((*str)[len], &flag);
        len += 1;
    }
    return (len);
}

int get_nums_splited(char *str, int (*sep_func)(char *, int *))
{
    int nums;
    int sep;

    nums = 0;
    sep = 0;
    while (*str)
    {
        str += get_len_to_next(&str, sep_func);
        str += sep_func(str, &sep);
        nums += 1;
    }
    return (nums);
}

char    *get_str(char *str, int len)
{
    char    *result;

    result = (char *)malloc(sizeof(char) * (len + 1));
    if (!result)
        return (0);
    result[len] = 0;
    ft_strlcpy(result, str, len);
    return (result);
}

char    **split_with_quote_flag(char *str, int (*sep_func)(char *, int *))
{
    char    **result;
    int     nums_splited;
    int     idx;
    int     len;
    int     sep;

    nums_splited = get_nums_splited(str, sep_func);
    result = malloc(sizeof(void *) * (nums_splited + 1));
    if (result == 0)
        return (0);
    result[nums_splited] = 0;
    idx = 0;
    sep = 0;
    while (idx < nums_splited)
    {
        len = get_len_to_next(&str, sep_func);
        result[idx] = get_str(str, len + 1);
        if (!result[idx])
            return (0);
        str += len;
        str += sep_func(str, &sep);
        idx += 1;
    }
    return (result);
}