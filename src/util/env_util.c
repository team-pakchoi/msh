/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 22:22:44 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/02 13:47:31 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env(char *name_and_value)
{
	t_list	*new;

	new = ft_lstnew(ft_strdup(name_and_value));
	ft_lstadd_back(&g_mini.env, new);
}

static unsigned int	env_name_len(const char *str)
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

// TODO: find_env(char *name)

void	remove_env(char	*name)
{
	t_list	*found;
	t_list	*before_found;

	found = g_mini.env;
	while (found)
	{
		if (!ft_strncmp((char *)found->content, name, env_name_len(found->content)))
			break ;
		before_found = found;
		found = found->next;
	}
	before_found->next = found->next;
	ft_lstdelone(found, free);
}

void	update_env(char *name, char *new_value)
{
	t_list	*found;
	char	*new;

	found = g_mini.env;
	while (found)
	{
		if (!ft_strncmp((char *)found->content, name, env_name_len(found->content)))
			break ;
		found = found->next;
	}
	new = ft_strjoin(ft_strndup((char *)found->content, env_name_len((char *)found->content) + 1), new_value);
	free(found->content);
	found->content = new;
}
