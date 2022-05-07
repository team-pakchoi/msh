/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 02:33:43 by sarchoi           #+#    #+#             */
/*   Updated: 2022/05/06 18:10:41 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	name_len(const char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		i++;
		if (str[i] == '=')
			break ;
	}
	return (i);
}

t_var	*find_var(char *name)
{
	t_var	*tmp;

	tmp = g_mini.env;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, name, name_len(name)) == 0 \
			&& tmp->var[name_len(name)] == '=')
			return (tmp);
		tmp = tmp->next;
	}
	return ((t_var *) NULL);
}

char	*find_var_value(char *name)
{
	t_var	*tmp;

	tmp = find_var(name);
	if (!tmp)
		return ((char *) NULL);
	return (tmp->var + name_len(tmp->var) + 1);
}

void	remove_var(char *name)
{
	t_var	*tmp;
	t_var	*before_tmp;

	tmp = g_mini.env;
	before_tmp = (t_var *) NULL;
	while (tmp)
	{
		if (!ft_strncmp(name, tmp->var, name_len(tmp->var)))
			break ;
		before_tmp = tmp;
		tmp = tmp->next;
	}
	if (tmp)
	{
		if (before_tmp)
			before_tmp->next = tmp->next;
		else
			g_mini.env = tmp->next;
		free(tmp->var);
		free(tmp);
	}
}

void	remove_var_list(void)
{
	t_var	*tmp;

	while (g_mini.env)
	{
		tmp = g_mini.env;
		g_mini.env = g_mini.env->next;
		free(tmp->var);
		free(tmp);
	}
}
