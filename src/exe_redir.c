
#include "minishell.h"

int exe_output_redir(char *command[], t_op op)
{
    int     file_fd;
    int		fds[2];
    char    *line;

    file_fd = open(command[0], O_WRONLY | O_CREAT | O_EXCL, 0644);
    if (file_fd == -1) 
    {
        if (op == OUTPUT)
            file_fd = open(command[0], O_WRONLY | O_TRUNC);
        else
            file_fd = open(command[0], O_WRONLY | O_APPEND);
    }
    pipe(fds);
    dup2(fds[1], STDOUT_FILENO);
    close(fds[1]);
    while (get_next_line(STDIN_FILENO, &line) > 0)
    {
        ft_putstr_fd(line, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
        ft_putstr_fd(line, file_fd);
        ft_putstr_fd("\n", file_fd);
        free(line);
    }
    close(file_fd);
    dup2(fds[0], STDIN_FILENO);
    close(fds[0]);
    restore_ori_stdout();
    return (1);
}

int exe_input_redir(char *command[])
{
    int     file_fd;
    int		fds[2];
    char    *line;

    pipe(fds);
    if (g_mini.cmd_idx == 1)
        close(STDIN_FILENO);
    dup2(fds[1], STDOUT_FILENO);
    close(fds[1]);
    while (get_next_line(STDIN_FILENO, &line) > 0)
    {
        ft_putstr_fd(line, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
        free(line);
        line = 0;
    }
    file_fd = open(command[0], O_RDONLY | O_EXCL);
    if (file_fd == -1) 
    {
        perror("no such file or directory");
        g_mini.exit_status = 127;
    }
    while (get_next_line(file_fd, &line) > 0)
    {
        ft_putstr_fd(line, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
        free(line);
        line = 0;
    }
    close(file_fd);
    dup2(fds[0], STDIN_FILENO);
    close(fds[0]);
    close(STDOUT_FILENO);
    restore_ori_stdout();
    return (1);
}