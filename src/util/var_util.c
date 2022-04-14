/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 02:33:43 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/14 18:02:31 by sarchoi          ###   ########seoul.kr  */
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
			break;
	}
	return (i);
}

static t_var	*var_new(char *var, int scope)
{
	t_var	*new;

	new = (t_var *)malloc(sizeof(t_var));
	if (!new)
		return ((t_var *)NULL);
	new->var = var;
	new->scope = scope;
	new->next = (t_var *)NULL;
	return (new);
}

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

void	add_var(char *name_and_value, int scope)
{
	t_var *tmp;
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

t_var	*find_var(char *name)
{
	t_var	*tmp;

	tmp = g_mini.env;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, name, name_len(name)) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return ((t_var *)NULL);
}

/*
** get var valye by name
*/
char	*find_var_value(char *name)
{
	t_var	*tmp;

	tmp = find_var(name);
	if (!tmp)
		return ((char *)NULL);
	return (tmp->var + name_len(tmp->var) + 1);
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

void	remove_var(char *name)
{
	t_var	*tmp;
	t_var	*before_tmp;

	tmp = g_mini.env;
	while (tmp)
	{
		if (!ft_strncmp(name, tmp->var, name_len(tmp->var)))
			break ;
		before_tmp = tmp;
		tmp = tmp->next;
	}
	before_tmp->next = tmp->next;
	free(tmp->var);
	free(tmp);
}

void	remove_var_list()
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
