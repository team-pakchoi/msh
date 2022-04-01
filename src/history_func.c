/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 01:43:29 by cpak              #+#    #+#             */
/*   Updated: 2022/04/01 01:43:38 by cpak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int init_history(int *fd)
{
    char    *line;

    *fd = open(".history", O_RDWR | O_CREAT | O_EXCL, 0644);
    if (*fd == -1) {
        *fd = open(".history", O_RDWR);
        while (get_next_line(*fd, &line) > 0)
        {
            add_history(line);
            free(line);
            line = 0;
        }
    }
    return (1);
}

int save_history(char *str, int fd)
{
    int len;

    if (str == 0)
        return (0);
    len = ft_strlen(str);
    if (len > 0) {
        write(fd, str, len);
        write(fd, "\n", 1);
        add_history(str);
    }
    return (1);
}
