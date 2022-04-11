/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:39:17 by cpak              #+#    #+#             */
/*   Updated: 2022/04/06 14:39:18 by cpak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    set_input_redir(t_cmd *node)
{
    t_cmd   *tar;
    t_cmd   *prev_tar;

    tar = find_last_cmd();
    while (tar->prev != 0 && tar->op != 1)
        tar = tar->prev;
    if (tar->prev == 0)
    {
        g_mini.cmd = node;
        node->next = tar;
        tar->prev = node;
        return ;
    }
    prev_tar = tar->prev;
    prev_tar->next = node;
    node->prev = prev_tar;
    node->next = tar;
    tar->prev = node;
}

int add_cmd(char *str, int op)
{
    t_cmd   *new;
    t_cmd   *last;

    new = (t_cmd *)malloc(sizeof(t_cmd));
    if (!new)
        return (0);
    new->str = str;
    new->op = op;
    new->next = 0;
    new->prev = 0;
    last = find_last_cmd();
    if (last == 0)
        g_mini.cmd = new;
    else
    {
        if (op == 4 || op == 5)
            set_input_redir(new);
        else
        {
            last->next = new;
            new->prev = last;
        }
    }
    g_mini.cmd_len += 1;
    return (1);
}

void    remove_cmd_list()
{
    t_cmd   *node;
    t_cmd   *prev;

    node = g_mini.cmd;
    while (node != 0)
    {
        prev = node;
        node = node->next;
        free(prev->str);
        prev->str = 0;
        prev->next = 0;
        free(prev);
    }
    g_mini.cmd = 0;
}

t_cmd   *find_nth_cmd(int idx)
{
    t_cmd   *node;

    node = g_mini.cmd;
    while (node != 0 && node->next != 0 && idx > 0)
    {
        node = node->next;
        idx -= 1;
    }
    return (node);
}

t_cmd   *find_last_cmd()
{
    t_cmd   *node;

    node = g_mini.cmd;
    while (node != 0 && node->next != 0)
        node = node->next;
    return (node);
}

void    read_all_cmd()
{
    t_cmd   *node;
    int     len;

    node = g_mini.cmd;
    len = g_mini.cmd_len;
    write(2, "------------------\n", 19);
    while (len > 0)
    {
        write(2, "str: ", 5);
        write(2, node->str, ft_strlen(node->str));
        write(2, ", op:", 5);
        write(2, ft_itoa(node->op), ft_strlen(ft_itoa(node->op)));
        write(2, "\n", 1);
        node = node->next;
        len -= 1;
    }
    write(2, "-----parsed-------\n", 19);
}
