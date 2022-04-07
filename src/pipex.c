/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 19:31:52 by cpak              #+#    #+#             */
/*   Updated: 2022/04/01 19:32:01 by cpak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int excute_input_redir(char *command[])
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
        // write(STDOUT_FILENO, "\n", 1);
        free(line);
        line = 0;
    }
    close(fd);
    close(STDOUT_FILENO);
    return (1);
}

int excute_output_redir(char *command[])
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

int execute_command(int idx, char *envp[])
{
    t_cmd   *cmd_node;
	char	**command;
    
    cmd_node = find_nth_cmd(idx);
    command = split_command(cmd_node->str, 32);
    parse_cmd(command);
    if (cmd_node->op == 1)
    {
        if (access(command[0], X_OK) != 0)
		command[0] = find_command_path(envp, command[0]);
        if (execve(command[0], command, envp) == -1)
        {
            perror("command not found");
            exit (127);
        }
    }
    if (cmd_node->op == 2 || cmd_node->op == 3)
        excute_input_redir(command);
    if (cmd_node->op == 4 || cmd_node->op == 5)
        excute_output_redir(command);
	return (1);
}

void	pipex(int idx, char *envp[])
{
	pid_t	pid;
	int		fds[2];
	int		status;

	pipe(fds);
	pid = fork();
	if (pid == 0 && idx > 0)
	{
		set_pipein_to_stdout(fds);
		pipex(idx - 1, envp);
        exit(0);
	}
	else if (pid != 0)
	{
		set_pipeout_to_stdin(fds);
		waitpid(pid, &status, 0);
		execute_command(idx, envp);
	}
}
