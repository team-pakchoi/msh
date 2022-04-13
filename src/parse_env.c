/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:41:00 by cpak              #+#    #+#             */
/*   Updated: 2022/04/07 16:41:03 by cpak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *get_parsed_str(char *str, char *env_name, char *env_value)
{
    char    *new;
    int     len_n;
    int     len_v;
    int     i;

    i = 0;
    len_n = ft_strlen(env_name);
    len_v = ft_strlen(env_value);
    new = ft_calloc(ft_strlen(str) - len_n + len_v + 1, sizeof(char));
    if (!new)
        return (0);
    while (ft_strncmp(str + i, env_name, len_n) != 0)
    {
        new[i] = str[i];
        i += 1;
    }
    while (*env_value)
    {
        new[i] = *env_value;
        i += 1;
        env_value += 1;
    }
    while (str[i - len_v + len_n])
    {
        new[i] = str[i - len_v + len_n];
        i += 1;
    }
    free(str);
    return (new);
}

char *trans_env_name_to_value(char *str, int start, int end)
{
    char    *env_name;
    char    *env_value;
    char    *parsed_str;

    env_name = ft_strndup(str + start, end - start);
    env_value = find_var_value(env_name + 1);
    parsed_str = get_parsed_str(str, env_name, env_value);
    free(env_name);
    return (parsed_str);
}

int get_next_env_point(char *str, int *start, int *end)
{
    int i;

    i = 0;
    *start = -1;
    while (str[i])
    {
        if (str[i] == '$')
            *start = i;
        else if (*start != -1 && !ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
        {
            *end = i;
            return (1);
        }
        i += 1;
    }
    if (*start != -1)
    {
        *end = i;
        return (1);
    }
    return (0);
}

int parse_str_env(char **str)
{
    int     start;
    int     end;
    
    while (get_next_env_point(*str, &start, &end))
    {
        *str = trans_env_name_to_value(*str, start, end);
    }
    return (1);
}

int parse_cmd_env(char **cmd)
{
    int idx;

    idx = 0;
    while (cmd[idx])
    {
        parse_str_env(&cmd[idx]);
        idx += 1;
    }
    return (1);
}