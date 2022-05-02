/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:26:10 by sarchoi           #+#    #+#             */
/*   Updated: 2022/05/03 03:35:09 by cpak             ###   ########seoul.kr  */
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

# define  FT_SUCCESS	1
# define  FT_ERROR		-1
# define  FT_TRUE		1
# define  FT_FALSE		0

typedef int	t_bool;

# define  PROMPT_STRING		" $ "
# define  PROMPT_HEREDOC	"heredoc> "

# define  PROMPT_COLOR_PWD		"\033[1;32m"
# define  PROMPT_COLOR_PROMPT	"\033[1;35m"
# define  PROMPT_COLOR_RESET	"\033[0m"

typedef enum e_op
{
	PIPE =		1,
	INPUT =		2,
	INPUT_D =	3,
	OUTPUT =	4,
	OUTPUT_D =	5
}	t_op;

typedef struct s_cmd
{
	char			**strarr;
	t_op			op;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}					t_cmd;

typedef struct s_var
{
	char			*var;
	int				scope;
	struct s_var	*next;
}					t_var;

/*
** value for `scope` the member of structure `t_var`
*/
# define  SHELL_VAR	0
# define  ENV_VAR	1

typedef struct s_history
{
	char			*prev_input;
	int				fd;
}					t_history;

typedef struct s_minishell
{
	t_history		history;
	char			*prompt_str;
	char			*prompt_input;
	t_cmd			*cmd;
	int				cmd_len;
	int				cmd_idx;
	t_var			*env;
	unsigned char	exit_status;
}					t_minishell;

t_minishell	g_mini;

/*
** init: env
*/
void	init_env(char **envp);

/*
** builtin
*/
void	ft_env(void);
void	ft_unset(char **cmds);
void	ft_export(char **cmds);
void	ft_exit(char **cmds);
void	ft_echo(char **cmds);
void	ft_cd(char **cmds);
void	ft_pwd(void);

/*
** util: cd
*/
int		valid_directory(char *path);
int		valid_permission(char *path);
int		has_directory(char *path);
void	set_pwd_env(void);

/*
** util: var
*/
t_var	*find_var(char *name);
char	*find_var_value(char *name);
void	remove_var(char *name);
void	remove_var_list(void);
void	add_var(char *name_and_value, int scope);
void	update_var(char *name, char *new_value);
char	**find_all_env(void);
int		is_valid_var_format(char *str);
int		is_valid_var_name(const char *str);

/*
** util: export
*/
void	print_sorted_env(void);

/*
** util: print
*/
void	print_strerror(char *cmd_str);
void	print_error(char *cmd_str, char *msg);
void	print_error2(char *cmd_str, char *arg_str, char *msg);
void	print_prompt(void);
void	print_cwd(void);

/*
** signal
*/
void	init_signal(void);
void	eof_handler(void);

/*
** prompt
*/
int		deal_prompt(void);

/*
** cmd
*/
int		deal_command(void);

int		add_cmd(char **strarr, t_op op);
void	remove_cmd_list(void);
t_cmd	*find_nth_cmd(int idx);
t_cmd	*find_last_cmd(void);
void	read_all_cmd(void);
void	read_arr(char **str);

/*
** parse
*/
int		is_quote(char c);
void	set_quotes_flag(char c, int *flag);
char	*change_str(char *str, char *str_tar, char *str_src);
int		parse_cmd_env(char ***strarr);
int		parse_str_env(char **str);
int		trans_all_env(char **str);
int		set_cmd_list(char *str);
int		check_quote_closed(char *str, int *flag);

/*
** split
*/
int		get_len_to_next(char **str, int (*sep_func)(char *, int *));
char	**split_with_quote(char *str, int (*sep_func)(char *, int *));

/*
** history
*/
int		init_history(void);
int		save_history(void);

/*
** pipex
*/
void	set_pipein_to_stdout(int *fds);
void	set_pipeout_to_stdin(int *fds);
void	set_fileout_to_fd(char *path, int fd);
void	set_filein_to_fd(char *path, int fd);
void	read_fd(int fd);
void	print_file(char *path);

void	set_self_pipe(void);
void	keep_ori_std(void);
void	restore_ori_stdin(void);
void	restore_ori_stdout(void);

int		exec_assign(char **command, t_cmd *cmd);
int		exec_builtin(char **cmd);
int		exec_execve(char **command);
int		exec_output_redir(char *command[], t_op op);
int		exec_input_redir(char *command[], t_op op);
void	exec_heredoc(char *command[], int out_fd);

int		is_op(char *str, int *sep_num);
int		is_white_space(char *str, int *sep_num);

#endif
