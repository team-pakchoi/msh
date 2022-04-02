/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:26:10 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/02 13:57:46 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

# define  FT_SUCCESS 1
# define  FT_ERROR -1
# define  FT_TRUE 1
# define  FT_FALSE 0
typedef int	t_bool;

typedef struct s_minishell
{
	t_list	*env;
} t_minishell;

t_minishell		g_mini;

/*
** env
*/
void	init_env(char **envp);
void	ft_env();

void	add_env(char *name_and_value);
void	remove_env(char	*name);
void	update_env(char *name, char *new_value);

/*
** history
*/
int init_history(int *fd);
int save_history(char *str, int fd);

#endif
