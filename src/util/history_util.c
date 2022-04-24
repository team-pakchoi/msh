/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 01:43:29 by cpak              #+#    #+#             */
/*   Updated: 2022/04/25 00:09:26 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int init_history(void)
{
    char    *line;
    int     result;

    result = 1;
    g_mini.history.fd = open(".history", O_RDWR | O_CREAT | O_EXCL, 0644);
    if (g_mini.history.fd == -1) {
        g_mini.history.fd = open(".history", O_RDWR);
        while (result > 0)
        {
            result = get_next_line(g_mini.history.fd, &line);
            if (result == 0)
                g_mini.history.prev_input = ft_strdup(line);
            else
                add_history(line);
            free(line);
        }
    }
    return (1);
}

int save_history(void)
{
    int len;

    if (g_mini.prompt_input == 0)
        return (0);
    len = ft_strlen(g_mini.prompt_input);
    if (len > 0 && ft_strcmp(g_mini.prompt_input, g_mini.history.prev_input))
    {
        write(g_mini.history.fd, g_mini.prompt_input, len);
        write(g_mini.history.fd, "\n", 1);
        add_history(g_mini.prompt_input);
        if (*g_mini.history.prev_input != 0)
            free(g_mini.history.prev_input);
        g_mini.history.prev_input = ft_strdup(g_mini.prompt_input);
    }
    return (1);
}
