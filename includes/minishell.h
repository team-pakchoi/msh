/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:26:10 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/07 14:35:12 by sarchoi          ###   ########seoul.kr  */
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
# include <sys/stat.h>
# include "libft.h"

# define  FT_SUCCESS 1
# define  FT_ERROR -1
# define  FT_TRUE 1
# define  FT_FALSE 0
typedef int	t_bool;

typedef struct s_cmd
{
  char            *str;
  int             op;
  struct s_cmd    *next;
  struct s_cmd    *prev;
} t_cmd;

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
  t_cmd   *cmd;
  int     cmd_len;
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
void	ft_echo(char **cmds);
void	ft_cd(char **cmds);

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
** cmd
*/
int     parse_command(char *str);
int     deal_command(char *str, char *envp[]);

int     add_cmd(char *str, int op);
void    remove_cmd_list();
t_cmd   *find_nth_cmd(int idx);
t_cmd   *find_last_cmd();
void    read_all_cmd();

/*
** history
*/
int     init_history(int *fd, char **prev);
int     save_history(int fd, char *str, char **prev);

/*
** pipex
*/
void	set_pipein_to_stdout(int *fds);
void	set_pipeout_to_stdin(int *fds);
void	set_fileout_to_fd(char *path, int fd);
void	set_filein_to_fd(char *path, int fd);
void    read_fd(int fd);
char	*find_command_path(char *envp[], char *command);
char	**split_command(char *cmd, char c);
int     execute_command(int idx, char *envp[]);
void	pipex(int idx, char *envp[]);

#endif
