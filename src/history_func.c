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

int init_history(int *fd, char **prev)
{
    char    *line;
    int     result;

    result = 1;
    *fd = open(".history", O_RDWR | O_CREAT | O_EXCL, 0644);
    if (*fd == -1) {
        *fd = open(".history", O_RDWR);
        while (result > 0)
        {
            result = get_next_line(*fd, &line);
            add_history(line);
            if (result == 0)
                *prev = ft_strdup(line);
            free(line);
        }
    }
    return (1);
}

int save_history(int fd, char *str, char **prev)
{
    int len;

    if (str == 0)
        return (0);
    len = ft_strlen(str);
    if (len > 0 && ft_strcmp(str, *prev)) {
        write(fd, str, len);
        write(fd, "\n", 1);
        add_history(str);
        free(*prev);
        *prev = ft_strdup(str);
    }
    return (1);
}
