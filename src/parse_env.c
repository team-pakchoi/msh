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

char    *change_str(char *str, char *str_tar, char *str_src)
{
    char    *new;
    int     len_tar;
    int     len_src;
    int     i;

    i = 0;
    len_tar = ft_strlen(str_tar);
    len_src = ft_strlen(str_src);
    new = ft_calloc(ft_strlen(str) - len_tar + len_src + 1, sizeof(char));
    if (!new)
        return (0);
    while (ft_strncmp(str + i, str_tar, len_tar) != 0)
    {
        new[i] = str[i];
        i += 1;
    }
    while (*str_src)
    {
        new[i] = *str_src;
        i += 1;
        str_src += 1;
    }
    while (str[i - len_src + len_tar])
    {
        new[i] = str[i - len_src + len_tar];
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
    parsed_str = change_str(str, env_name, env_value);
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

char *get_next_str(char *str, int *idx, int *sep)
{
    int     start;
    char    *result;

    start = *idx;
    if (str[*idx] == '"' || str[*idx] == '\'')
        *sep = str[*idx];
    else
        *sep = -1;
    *idx += 1;
    while (str[*idx])
    {
        if (*sep == str[*idx])
            break ;
        if (*sep == -1 && (str[*idx] == '"' || str[*idx] == '\''))
            break ;
        *idx += 1;
    }
    if (*idx - start - 1 <= 0)
        return (0);
    result = ft_strndup(str + start, *idx - start + 1);
    return (result);
}

int trans_all_env(char **str)
{
    int     start;
    int     end;

    while (get_next_env_point(*str, &start, &end))
    {
        *str = trans_env_name_to_value(*str, start, end);
        if (*str == 0)
            return (0);
    }
    return (1);
}

int parse_str_env(char **str)
{
    int     idx;
    char    *tar;
    char    *src;
    int     sep;
   
    idx = 0;
    while ((*str)[idx])
    {
        tar = get_next_str(*str, &idx, &sep);
        if (tar == 0)
            continue ;
        src = ft_strtrim(tar, (const char *)&sep);
        if (sep != '\'')
        {
            if (trans_all_env(&src) == 0)
                return (0);
        }
        *str = change_str(*str, tar, src);
        idx += ft_strlen(src) - ft_strlen(tar);
        free(src);
        free(tar);
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