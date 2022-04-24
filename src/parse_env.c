/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanul <chanul@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:41:00 by cpak              #+#    #+#             */
/*   Updated: 2022/04/24 23:51:56 by chanul           ###   ########.fr       */
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
    new = (char *)ft_calloc(ft_strlen(str) - len_tar + len_src + 1, sizeof(char));
    if (!new)
        return (0);
    while (ft_strncmp(str + i, str_tar, len_tar) != 0)
    {
        new[i] = str[i];
        i += 1;
    }
    while (str_src && *str_src)
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

char *trans_env_name_to_value(char *str, int start, int end, int *idx)
{
    char    *env_name;
    char    *env_value;
    char    *parsed_str;

    env_name = ft_strndup(str + start, end - start);
    if (env_name[1] == '?')
        env_value = ft_itoa((int)g_mini.exit_status);
    else
        env_value = find_var_value(env_name + 1);
    parsed_str = change_str(str, env_name, env_value);
    *idx = start + ft_strlen(env_value);
    if (env_name[1] == '?')
        free(env_value);
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
        else if (*start != -1)
        {            
            if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
            {
                if (i - *start == 1 && str[i] == '?')
                    i += 1;
                *end = i;
                return (1);
            }
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

char    *get_next_str(char *str, int *idx, int *sep)
{
    int     start;

    start = *idx;
    *sep = 0;
    if (str[*idx] == '"' || str[*idx] == '\'')
    {
        *sep = str[*idx];
        *idx += 1;
    }
    while (str[*idx])
    {
        if (*sep == str[*idx])
            return (ft_strndup(str + start, *idx - start + 1));
        else if (*sep == 0 && (str[*idx] == '"' || str[*idx] == '\''))
            return (ft_strndup(str + start, *idx - start));
        *idx += 1;
    }
    *sep = 0;
    return (ft_strndup(str + start, *idx - start));
}

int trans_all_env(char **str)
{
    int     start;
    int     end;
    int     idx;

    idx = 0;
    while (get_next_env_point(*str + idx, &start, &end))
    {
        *str = trans_env_name_to_value(*str + idx, start, end, &idx);
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
    sep = 0;
    while ((*str)[idx])
    {
        tar = get_next_str(*str, &idx, &sep);
        if (tar == 0)
            continue ;
        if (sep == 0)
            src = ft_strdup(tar);
        else
            src = ft_strtrim(tar, (const char *)&sep);
        if (sep != '\'')
        {
            if (trans_all_env(&src) == 0)
                return (0);
        }
        *str = change_str(*str, tar, src);
        idx -= ft_strlen(tar);
        idx += ft_strlen(src);
        if (sep != 0)
            idx += 1;
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