/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:26:36 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/03 13:54:30 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int deal_command(char *str, char *envp[]) {
    pid_t   pid;
    int     status;
    int     fds[2];
    char    **cmd;

    pipe(fds);
    pid = fork();
    if (pid == 0)
    {
        // 명령 문자열 분할
        cmd = ft_split(str, '|');

        set_pipein_to_stdout(fds);
        pipex(ft_strarr_len(cmd), cmd, envp);
        exit(0);
    }
    else
    {
        set_pipeout_to_stdin(fds);
        waitpid(pid, &status, 0);
    }
    return (1);
}

static void	free_global()
{
	remove_var_list();
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	int		his_fd;

	(void)argc;
	(void)argv;
	init_env(envp);
	init_history(&his_fd);
	while(1)
	{
		str = readline("prompt : ");
		if (!str)
			return (0);
    deal_command(str, envp);
    read_fd(STDIN_FILENO);
    save_history(str, his_fd);
    free(str);
  }
  free_global();
	return(EXIT_SUCCESS);
}
