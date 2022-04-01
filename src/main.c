/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:26:36 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/01 22:35:31 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_global()
{
	ft_lstclear(&g_mini.env, free);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	init_env(envp);
	ft_env();

	free_global();
	return (EXIT_SUCCESS);
}
