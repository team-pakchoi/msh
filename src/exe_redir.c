
#include "minishell.h"

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