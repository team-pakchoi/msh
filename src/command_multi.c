/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_multi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 06:37:57 by cpak              #+#    #+#             */
/*   Updated: 2022/05/11 07:33:18 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 모든 프로세스가 종료되기까지 기다린다.
static void	wait_child(pid_t *pid_arr)
{
	int	idx;
	int	status;

	idx = 0;
	while (pid_arr[idx])
	{
		waitpid(pid_arr[idx], &status, 0);
		set_exit_status(status);
		idx += 1;
	}
	free(pid_arr);
}

	// 이전 pipeout을 stdin에 연결
	// 그러나 첫번째이고 cat 명령어라면 stdin을 닫는다.
	// 현재 pipein을 stdout에 연결
	// 마지막 명령어는 stdout을 사용하므로 pipe을 모두 닫는다.
	// 명령어를 실행한다.
static int	child_exec(int *fds, int pre_pipeout, int cmd_idx)
{
	t_cmd	*cmd;

	cmd = find_nth_cmd(cmd_idx);
	if (pre_pipeout != -1)
		set_fd_to_stdin(pre_pipeout);
	else if (ft_strcmp(cmd->strarr[0], "cat"))
		close(STDIN_FILENO);
	if (cmd_idx != g_mini.cmd_len - 1)
		set_pipein_to_stdout(fds);
	else
	{
		close(fds[0]);
		close(fds[1]);
	}
	exec_cmd_node(cmd);
	exit(g_mini.exit_status);
	return (0);
}

// 이전 pipeout을 닫기
// 현재 pipein을 닫기
// 현재 pipeout을 pre_pipout에 저장
static void	parent_set(int *fds, int *pre_pipeout)
{
	if (*pre_pipeout != -1)
		close(*pre_pipeout);
	close(fds[1]);
	*pre_pipeout = fds[0];
}

int	exec_multi_cmd(void)
{
	pid_t	pid;
	int		cmd_idx;
	int		fds[2];
	int		pre_pipeout;
	pid_t	*pid_arr;

	cmd_idx = 0;
	pre_pipeout = -1;
	pid_arr = (pid_t *)ft_calloc(g_mini.cmd_len + 1, sizeof(pid_t));
	if (!pid_arr)
		return (0);
	while (cmd_idx < g_mini.cmd_len)
	{
		pipe(fds);
		pid = fork();
		if (pid == 0)
			return (child_exec(fds, pre_pipeout, cmd_idx));
		parent_set(fds, &pre_pipeout);
		pid_arr[cmd_idx] = pid;
		cmd_idx += 1;
	}
	close(pre_pipeout);
	wait_child(pid_arr);
	return (1);
}
