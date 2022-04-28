#include "pipex.h"

int execute_command(char *cmd, char *envp[])
{
	char    **command;

	command = split_command(cmd);
	if (access(command[0], X_OK) != 0)
		command[0] = find_command_path(envp, command[0]);
	if (execve(command[0], command, envp) == -1)
	{
		perror("command not found");
		exit (127);
	}
	return (1);
}

int main(int argc, char *argv[], char *envp[])
{
  execute_command(argv[1], envp);
  return (0);
}

// cc -o test execve.c split_command.c find_path.c ft_split.c ft_strjoin.c ft_strnstr.c ft_strtrim.c
