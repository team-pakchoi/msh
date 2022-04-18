/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:26:10 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/16 20:58:12 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <termios.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include "libft.h"

# define  FT_SUCCESS 1
# define  FT_ERROR -1
# define  FT_TRUE 1
# define  FT_FALSE 0
typedef int	t_bool;

# define  PROMPT_STRING "prompt : "
# define  PROMPT_QUOTE "quote> "
# define  PROMPT_QUOTE_D "dquote> "

typedef enum  e_op
{
  PIPE = 1,
  INPUT = 2,
  INPUT_D = 3,
  OUTPUT = 4,
  OUTPUT_D = 5
} t_op;

typedef struct s_cmd
{
  char            *str;
  t_op            op;
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
void	ft_pwd();

/*
** util: var
*/
int	is_valid_var_format(char *str);
int	is_valid_var_name(const char *str);
void	add_var(char *name_and_value, int scope);
t_var	*find_var(char *name);
char	*find_var_value(char *name);
char	**find_all_env();
void	update_var(char *name, char *new_value);
void	remove_var(char *name);
void	remove_var_list();

/*
** util: print
*/
void	print_strerror(char *cmd_str);
void	print_error(char *cmd_str, char *msg);
void	print_error2(char *cmd_str, char *arg_str, char *msg);

/*
** signal
*/
void	init_signal();

/*
** prompt
*/
int     deal_prompt(char **input, int quote);

/*
** cmd
*/
int     set_cmd_list(char *str);
int     deal_command(char *str);


int     add_cmd(char *str, t_op op);
void    remove_cmd_list();
t_cmd   *find_nth_cmd(int idx);
t_cmd   *find_last_cmd();
void    read_all_cmd();
void    read_arr(char **str);

/*
** parse
*/
void    set_quotes_flag(char c, int *flag);
int     parse_cmd_env(char **cmd);
int     parse_str_env(char **str);

/*
** split
*/
int     get_len_to_next(char **str, int (*sep_func)(char *, int *));
char    **split_with_quote_flag(char *str, int (*sep_func)(char *, int *));

/*
** history
*/
int     init_history(int *fd, char **prev);
int     save_history(int fd, char *str, char **prev);

/*
** pipex
*/
void	  set_pipein_to_stdout(int *fds);
void	  set_pipeout_to_stdin(int *fds);
void	  set_fileout_to_fd(char *path, int fd);
void	  set_filein_to_fd(char *path, int fd);
void    read_fd(int fd);
char	  *find_command_path(char *command);
int     execute_nth_cmd(int idx);
void	  pipex(int idx);

#endif
