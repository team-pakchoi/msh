#include "minishell.h"

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
    last = find_last_cmd();
    if (last == 0)
        g_mini.cmd = new;
    else
        last->next = new;
    g_mini.cmd_len += 1;
    return (1);
}

t_cmd   *find_nth_cmd(int idx)
{
    t_cmd   *node;

    node = g_mini.cmd;
    while (node != 0 && node->next != 0 && idx < 0)
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

