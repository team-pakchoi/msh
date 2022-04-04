/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 14:20:03 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/04 17:30:23 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(char *str)
{
	t_var	*tmp;

	if (!str)
		return (ft_env());
	if (ft_strchr(str, '='))
	{
		add_var(str, ENV_VAR);
		return (FT_SUCCESS);
	}
	tmp = find_var(str);
	if (!tmp)
		return (FT_ERROR);
	tmp->scope = ENV_VAR;
	return (FT_SUCCESS);
}
