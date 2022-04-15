#include "minishell.h"

int find_command_builtin(char **cmd)
{
    if (!ft_strcmp(*cmd, "cd"))
    {
        ft_cd(cmd);
        return (1);
    }
    else if (!ft_strcmp(*cmd, "echo"))
    {
        ft_echo(cmd);
        return (1);
    }
    else if (!ft_strcmp(*cmd, "env"))
    {
        ft_env(cmd);
        return (1);
    }
    else if (!ft_strcmp(*cmd, "exit"))
    {
        ft_exit(cmd);
        return (1);
    }
    else if (!ft_strcmp(*cmd, "export"))
    {
        ft_export(cmd);
        return (1);
    }
    else if (!ft_strcmp(*cmd, "pwd"))
    {
        ft_pwd(cmd);
        return (1);
    }
    else if (!ft_strcmp(*cmd, "unset"))
    {
        ft_unset(cmd);
        return (1);
    }
    return (0);
}

int execute_command(char **command, char *envp[])
{
    if (find_command_builtin(command) == 1)
        exit(0);
    if (access(command[0], X_OK) != 0)
    command[0] = find_command_path(envp, command[0]);
    if (execve(command[0], command, envp) == -1)
    {
        perror("command not found");
        exit (127);
    }
    return (1);
}

int execute_input_redir(char *command[])
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
        write(fd, line, ft_strlen(line));
        write(STDOUT_FILENO, line, ft_strlen(line));
        write(fd, "\n", 1);
        write(STDOUT_FILENO, "\n", 1);
        free(line);
        line = 0;
    }
    close(fd);
    close(STDOUT_FILENO);
    return (1);
}

int execute_output_redir(char *command[])
{
    int     fd;
    int     len;
    char    *line;

    len = 1;
    while (len > 0)
    {
        len = get_next_line(STDIN_FILENO, &line);
        write(STDOUT_FILENO, line, ft_strlen(line));
        write(STDOUT_FILENO, "\n", 1);
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
        write(STDOUT_FILENO, line, ft_strlen(line));
        write(STDOUT_FILENO, "\n", 1);
        free(line);
        line = 0;
    }
    close(fd);
    close(STDOUT_FILENO);
    return (1);
}

int is_white_space(char *str, int *sep_num)
{
    if (*str == 32)
        *sep_num = 1;
    else
        *sep_num = 0;
    return (*sep_num);
}

int execute_nth_cmd(int idx, char *envp[])
{
    t_cmd   *cmd_node;
	char	**command;
    
    cmd_node = find_nth_cmd(idx);
    command = split_with_quote_flag(cmd_node->str, is_white_space);
    parse_cmd_env(command);
    if (cmd_node->op == 1)
        execute_command(command, envp);
    if (cmd_node->op == 2 || cmd_node->op == 3)
        execute_input_redir(command);
    if (cmd_node->op == 4 || cmd_node->op == 5)
        execute_output_redir(command);
	return (1);
}