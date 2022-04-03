/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:26:10 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/03 02:30:02 by sarchoi          ###   ########seoul.kr  */
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

typedef struct	s_var
{
	char					*var;
	int						scope;
	struct s_var	*next;
}				t_var;

/*
** value for `scope` the member of structure `t_var`
*/
# define  SHELL_VAR 0
# define  ENV_VAR 1

typedef struct s_minishell
{
	t_list	*env;
} t_minishell;

t_minishell		g_mini;

/*
** env
*/
void	init_env(char **envp);
int		ft_env();

/*
** util: var
*/
void	add_var(t_var *list, char *name_and_value, int scope);
char	*find_var_value(t_var *list, char *name);
void	update_var(t_var *list, char *name, char *new_value);
void	remove_var(t_var *list, char *name);

/*
** history
*/
int init_history(int *fd);
int save_history(char *str, int fd);

void	set_pipein_to_stdout(int *fds);
void	set_pipeout_to_stdin(int *fds);
void	set_fileout_to_fd(char *path, int fd);
void	set_filein_to_fd(char *path, int fd);
void    read_fd(int fd);
char	*find_command_path(char *envp[], char *command);
char	**split_command(char *cmd);
int     execute_command(char *cmd, char *envp[]);
void	pipex(int idx, char *cmd[], char *envp[]);

#endif
