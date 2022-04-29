/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 23:12:28 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/30 01:28:55 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**list_to_array(t_var *list)
{
	char	**array;
	t_var	*tmp;
	int		i;

	i = 0;
	tmp = list;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	array = (char **)malloc(sizeof(char *) * (i + 1));
	tmp = list;
	i = 0;
	while (tmp)
	{
		array[i] = ft_strdup(tmp->var);
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

static void	sort_array(char **array)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (array[i])
	{
		j = i;
		while (array[j])
		{
			if (ft_strcmp(array[i], array[j]) > 0)
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_putstr_fd(array[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

static void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	print_sorted_env(void)
{
	char	**array;

	array = list_to_array(g_mini.env);
	sort_array(array);
	print_array(array);
	free_array(array);
}
