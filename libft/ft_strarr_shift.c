/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 19:32:30 by cpak              #+#    #+#             */
/*   Updated: 2022/04/01 19:32:39 by cpak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    **ft_strarr_shift(char ***strarr)
{
    char    **result;
    char    **new_arr;
    int     idx;

    result = (char **)malloc(sizeof(char **) * 2);
    if (!result)
        return ((char **)0);
    result[0] = (*strarr)[0];
    result[1] = 0;
    new_arr = (char **)malloc(sizeof(char **) * ft_strarr_len(*strarr));
    if (!new_arr)
        return ((char **)0);
    new_arr[ft_strarr_len(*strarr) - 1] = 0;
    idx = 1;
    while ((*strarr)[idx])
    {
        new_arr[idx - 1] = (*strarr)[idx];
        idx += 1;
    }
    free(*strarr);
    *strarr = new_arr;
    return (result);
}