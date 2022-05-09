/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:08:32 by sarchoi           #+#    #+#             */
/*   Updated: 2022/05/09 15:40:43 by cpak             ###   ########seoul.kr  */
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
	if (!new)
	{
		ft_putstr_fd("minishell: malloc error", 2);
		return ;
	}
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
	t_var	*exist_var;
	char	*new;
	char	*tmp;

	exist_var = find_var(name);
	if (!exist_var)
		return ;
	new = ft_strjoin(name, "=");
	tmp = new;
	new = ft_strjoin(new, new_value);
	free(tmp);
	free(exist_var->var);
	exist_var->var = new;
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
	arr[idx] = 0;
	while (tmp)
	{
		arr[idx] = ft_strdup(tmp->var);
		tmp = tmp->next;
		idx += 1;
	}
	return (arr);
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
