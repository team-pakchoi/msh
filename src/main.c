/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:26:36 by sarchoi           #+#    #+#             */
/*   Updated: 2022/03/31 14:43:06 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    char    *str;
    int     his_fd;

    init_history(&his_fd);
    while(1)
    {
        str = readline("prompt : ");
        if (str)
            printf("%s\n", str);
        else
            return (0);
            
        save_history(str, his_fd);
        free(str);
    }
    return(0);
}
