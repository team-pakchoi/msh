/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 00:09:03 by cpak              #+#    #+#             */
/*   Updated: 2022/04/27 12:08:10 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(char **cmd)
{
    if (!ft_strcmp(*cmd, "cd"))
        return (1);
    if (!ft_strcmp(*cmd, "echo"))
        return (2);
    if (!ft_strcmp(*cmd, "env"))
        return (3);
    if (!ft_strcmp(*cmd, "exit"))
        return (4);
    if (!ft_strcmp(*cmd, "export"))
        return (5);
    if (!ft_strcmp(*cmd, "pwd"))
        return (6);
    if (!ft_strcmp(*cmd, "unset"))
        return (7);
    return (0);
}

void route_builtin(char **cmd, int n)
{
    if (n == 1)
        return (ft_cd(cmd));
    if (n == 2)
        return (ft_echo(cmd));
    if (n == 3)
        return (ft_env());
    if (n == 4)
        return (ft_exit(cmd));
    if (n == 5)
        return (ft_export(cmd));
    if (n == 6)
        return (ft_pwd());
    if (n == 7)
        return (ft_unset(cmd));
}

int exec_builtin(char **cmd)
{
    int n;

    n = is_builtin(cmd);
    if (n)
    {
        if (g_mini.cmd_len != g_mini.cmd_idx)
            set_self_pipe();
        route_builtin(cmd, n);
        restore_ori_stdout();
    }
    return (n);
}

int exec_execve(char **command)
{
    pid_t   pid;
    int     fds[2];
    int     status;
    char    **envp;

    pipe(fds);
    pid = fork();
    if (pid == 0)
    {
        if (g_mini.cmd_len != g_mini.cmd_idx)
            set_pipein_to_stdout(fds);
        envp = find_all_env();
        if (**command == 0)
            return (0);
        if (execve(find_command_path(command[0]), command, envp) == -1)
        {
            print_error(command[0], "command not found");
            exit (127);
        }
        return (0);
    }
    if (g_mini.cmd_len != g_mini.cmd_idx)
        set_pipeout_to_stdin(fds);
    waitpid(pid, &status, 0);
    g_mini.exit_status = status;
    return (1);
}

int is_assign_cmd(char *str)
{
    int idx;
    
    idx = 0;
    while (str[idx])
    {
        if (!ft_isalpha(str[idx]) && !ft_isdigit(str[idx]) && str[idx] != '_')
            break ;
        idx += 1;
    }
    return (str[idx] == '=');
}

int exec_assign(char **command, t_cmd *cmd)
{
    int     idx;

    idx = 0;
    while (command[idx])
    {
        if (is_assign_cmd(command[idx]) == 0)
            break ;
        idx += 1;
    }
    if (command[idx] == 0)
    {
        if (cmd->prev && cmd->prev->op == 1)
            return (-1);
        if (cmd->next && cmd->next->op == 1)
            return (-1);
        set_var(command);
        set_self_pipe();
        restore_ori_stdout();
    }
    return (idx);
}
