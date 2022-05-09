/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:37:51 by sarchoi           #+#    #+#             */
/*   Updated: 2022/05/09 15:04:54 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_term(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

static void	sigint_handler(int signo)
{
	if (signo != SIGINT || errno != EINTR)
	{
		g_mini.exit_status = 130;
		return ;
	}
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_mini.exit_status = 1;
}

void	init_signal(void)
{
	init_term();
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	eof_handler(void)
{
	ft_putstr_fd("\033[1A", 1);
	ft_putstr_fd(g_mini.prompt_str, 1);
	ft_putstr_fd("exit\n", 1);
}
