/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:08:31 by owatanab          #+#    #+#             */
/*   Updated: 2024/11/18 14:03:15 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		g_signal;

void	parent(int signum)
{
	if (signum == SIGINT)
		g_signal = 2;
	if (signum == SIGQUIT)
	{
		g_signal = 3;
		ft_putstr_fd("Quit: 3\n", 2);
	}
}

void	read_handler(int signum)
{
	(void)signum;
	g_signal = 1;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	init_sigaction(t_shell *shell)
{
	if (sigemptyset(&shell->sa.sa_mask) == -1)
		error_exit("sigemptyset");
	// shell->sa.sa_handler = ignore;
	// if (sigaction(SIGQUIT, &shell->sa, NULL) == -1)
	//     error_exit("sigaction");
}

void	heredoc_handler(int signum)
{
	(void)signum;
	g_signal = 1;
	printf("\nminishell ");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	check_ctrl_c(t_shell *shell)
{
	if (g_signal == 1)
	{
		shell->exit_status = 1;
		g_signal = 0;
	}
}
