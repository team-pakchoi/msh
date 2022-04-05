/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:26:10 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/05 22:58:16 by sarchoi          ###   ########seoul.kr  */
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
	t_var	*env;
	unsigned char	exit_status;
} t_minishell;

t_minishell		g_mini;

/*
** init: env
*/
void	init_env(char **envp);

/*
** builtin
*/
void	ft_env();
void	ft_unset(char **cmds);
void	ft_export(char **cmds);
void	ft_exit(char **cmds);
int		ft_echo(char **args);

/*
** util: var
*/
int	is_valid_var_name(const char *str);
void	add_var(char *name_and_value, int scope);
t_var	*find_var(char *name);
char	*find_var_value(char *name);
void	update_var(char *name, char *new_value);
void	remove_var(char *name);
void	remove_var_list();

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
