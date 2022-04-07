/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:09:43 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/07 15:13:55 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, 1);
	ft_putchar_fd('\n', 1);
	g_mini.exit_status = 0;
	free(pwd);
}
