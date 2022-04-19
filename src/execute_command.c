#include "minishell.h"

void    set_pipe()
{
    int		fds[2];

	pipe(fds);
    dup2(fds[0], STDIN_FILENO);
    dup2(fds[1], STDOUT_FILENO);
    close(fds[0]);
    close(fds[1]);
}

int exe_builtin(char **cmd)
{
    if (!ft_strcmp(*cmd, "cd"))
    {
        set_pipe();
        ft_cd(cmd);
        restore_ori_stdout();
        return (1);
    }
    else if (!ft_strcmp(*cmd, "echo"))
    {
        set_pipe();
        ft_echo(cmd);
        restore_ori_stdout();
        return (1);
    }
    else if (!ft_strcmp(*cmd, "env"))
    {
        set_pipe();
        ft_env(cmd);
        restore_ori_stdout();
        return (1);
    }
    else if (!ft_strcmp(*cmd, "exit"))
    {
        set_pipe();
        ft_exit(cmd);
        restore_ori_stdout();
        return (1);
    }
    else if (!ft_strcmp(*cmd, "export"))
    {
        set_pipe();
        ft_export(cmd);
        restore_ori_stdout();
        return (1);
    }
    else if (!ft_strcmp(*cmd, "pwd"))
    {
        set_pipe();
        ft_pwd(cmd);
        restore_ori_stdout();
        return (1);
    }
    else if (!ft_strcmp(*cmd, "unset"))
    {
        set_pipe();
        ft_unset(cmd);
        restore_ori_stdout();
        return (1);
    }
    return (0);
}

int exe_execve(char **command)
{
    pid_t   pid;
    int     fds[2];
    int     status;
    char    **envp;

    pipe(fds);
    pid = fork();
    if (pid == 0)
    {
        set_pipein_to_stdout(fds);
        envp = find_all_env();
        if (access(command[0], X_OK) != 0)
        command[0] = find_command_path(command[0]);
        if (execve(command[0], command, envp) == -1)
        {
            perror("command not found");
            exit (127);
        }
    }
    else
    {
        set_pipeout_to_stdin(fds);
        waitpid(pid, &status, 0);
        g_mini.exit_status = status;
    }
    return (1);
}

int exe_input_redir(char *command[])
{
    int     fd;
    int     len;
    char    *line;

    len = 1;
    fd = open(command[0], O_RDWR | O_CREAT | O_EXCL, 0644);
    if (fd == -1) {
        fd = open(command[0], O_RDWR);
    }
    while (len > 0)
    {
        len = get_next_line(STDIN_FILENO, &line);
        ft_putstr_fd(line, fd);
        ft_putstr_fd("\n", fd);
        free(line);
        line = 0;
    }
    close(fd);
    return (1);
}

int exe_output_redir(char *command[])
{
    int     fd;
    int     len;
    char    *line;

    len = 1;
    while (len > 0)
    {
        len = get_next_line(STDIN_FILENO, &line);
        ft_putstr_fd(line, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
        free(line);
        line = 0;
    }
    fd = open(command[0], O_RDWR | O_CREAT | O_EXCL, 0644);
    if (fd == -1) {
        fd = open(command[0], O_RDWR);
    }
    len = 1;
    while (len > 0)
    {
        len = get_next_line(fd, &line);
        ft_putstr_fd(line, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
        free(line);
        line = 0;
    }
    close(fd);
    close(STDOUT_FILENO);
    return (1);
}