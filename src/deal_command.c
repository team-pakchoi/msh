/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:39:03 by cpak              #+#    #+#             */
/*   Updated: 2022/04/06 14:39:04 by cpak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_is_sep(char *str, int *sep_num)
{
    if (str[0] == '|')
    {
        *sep_num = 1;
        return (1);
    }
    if (str[0] == '<')
    {
        if (str[1] == '<')
        {
            *sep_num = 3;
            return (2);
        }
        else if (str[1] == '>')
        {
            *sep_num = -1;  // error
            return (2);
        }
        *sep_num = 2;
        return (1);
    }
    if (str[0] == '>')
    {
        if (str[1] == '>')
        {
            *sep_num = 5;
            return (2);
        }
        else if (str[1] == '<')
        {
            *sep_num = -1;  // error
            return (2);
        }
        *sep_num = 4;
        return (1);
    }
    *sep_num = 0;
    return (0);
}

int is_white_space(char *str, int *sep_num)
{
    if (*str == 32)
        *sep_num = 1;
    else
        *sep_num = 0;
    return (*sep_num);
}

void    set_redir_rest(char **strarr)
{
    t_cmd   *node;
    char    **new_arr;

    node = find_last_cmd();
    if (node)
    {
        new_arr = ft_strarr_join(node->strarr, strarr);
        free(node->strarr);
        free(strarr);
        node->strarr = new_arr;
        return ;
    }
    add_cmd(strarr, 1);
}

int set_cmd_list(char *str)
{
    char    **arr;
    int     sep;
    char    **strarr;
    char    **shifted;

    while (is_white_space(str, &sep))
        str += 1;
    arr = split_with_quote_flag(str, get_is_sep);
    if (get_is_sep(str, &sep) == 0)
        sep = 1;
    read_arr(arr);
    while (*arr)
    {
        strarr = split_with_quote_flag(*arr, is_white_space);
        parse_cmd_env(strarr);   
        if (sep != 1)
        {
            shifted = ft_strarr_shift(&strarr);
            set_redir_rest(strarr);
            if (add_cmd(shifted, sep) == 0)
                return (0);
        }
        else 
        {
            if (add_cmd(strarr, sep) == 0)
                return (0);
        }
        str += get_len_to_next(&str, get_is_sep);
        str += get_is_sep(str, &sep);
        arr += 1;
    }
    return (1);
}

int deal_cmd_node(t_cmd *cmd)
{
	char	**command;
    
    command = cmd->strarr;
    if (cmd->op == PIPE)
    {
        if (exec_builtin(command) == 0)
            exec_execve(command);
    }
    else if (cmd->op == INPUT || cmd->op == INPUT_D)
        exec_input_redir(command, cmd->op);
    else if (cmd->op == OUTPUT || cmd->op == OUTPUT_D)
        exec_output_redir(command, cmd->op);
	return (1);
}

int deal_command(char *str)
{
    t_cmd   *cmd;

    if (str == 0 || *str == 0)
        return (0);
    if (set_cmd_list(str) == 0)
        return (0);
    g_mini.cmd_idx = 1;
    cmd = g_mini.cmd;
    while (cmd)
    {
        deal_cmd_node(cmd);
        cmd = cmd->next;
        g_mini.cmd_idx += 1;
    }
    return (1);
}
