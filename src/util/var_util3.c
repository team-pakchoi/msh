/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_util3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:08:55 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/19 16:09:15 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_var_format(char *str)
{
	char	*tmp;
	char	*name;

	tmp = ft_strchr(str, '=');
	if (!tmp)
		return (FT_FALSE);
	name = ft_strndup(str, tmp - str);
	if (!is_valid_var_name(name))
	{
		free(name);
		return (FT_FALSE);
	}
	free(name);
	return (FT_TRUE);
}

int	is_valid_var_name(const char *str)
{
	unsigned int	i;

	i = 0;
	if (!str)
		return (FT_FALSE);
	if (str[0] == '=' || ft_isdigit(str[0]))
		return (FT_FALSE);
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
			return (FT_FALSE);
		i++;
	}
	return (FT_TRUE);
}
