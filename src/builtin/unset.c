/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 13:17:37 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/03 14:08:19 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char *var_name)
{
	if (!find_var_value(var_name))
		return (FT_SUCCESS);
	remove_var(var_name);
	return (FT_SUCCESS);
}
