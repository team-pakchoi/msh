/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_util2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:08:32 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/19 16:09:19 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_var	*var_new(char *var, int scope)
{
	t_var	*new;

	new = (t_var *)malloc(sizeof(t_var));
	if (!new)
		return ((t_var *) NULL);
	new->var = var;
	new->scope = scope;
	new->next = (t_var *) NULL;
	return (new);
}

void	add_var(char *name_and_value, int scope)
{
	t_var	*tmp;
	t_var	*new;

	tmp = g_mini.env;
	new = var_new(ft_strdup(name_and_value), scope);
	if (!tmp)
	{
		g_mini.env = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	update_var(char *name, char *new_value)
{
	t_var	*tmp;
	char	*new;

	tmp = find_var(name);
	if (!tmp)
		return ;
	new = ft_strjoin(name, "=");
	new = ft_strjoin(new, new_value);
	free(tmp->var);
	tmp->var = new;
}

char	**find_all_env(void)
{
	char	**arr;
	t_var	*tmp;
	int		idx;

	idx = 0;
	tmp = g_mini.env;
	while (tmp)
	{
		tmp = tmp->next;
		idx += 1;
	}
	arr = malloc(sizeof(char *) * (idx + 1));
	if (!arr)
		return ((char **) NULL);
	idx = 0;
	tmp = g_mini.env;
	while (tmp)
	{
		arr[idx] = ft_strdup(tmp->var);
		tmp = tmp->next;
		idx += 1;
	}
	return (arr);
}