/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 15:08:31 by owatanab          #+#    #+#             */
/*   Updated: 2024/11/16 20:23:43 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int g_signal;

void    parent(int signum)
{
    (void)signum;
    ++g_signal;
    if (2 <= g_signal)
    {
        g_signal = -1;
        return ;
    }
    kill(0, SIGINT);
}

void    read_handler(int signum)
{
    (void)signum;
    printf("\n");
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void    init_sigaction(t_shell *shell)
{
    if (sigemptyset(&shell->sa.sa_mask) == -1)
        error_exit("sigemptyset");
    shell->sa.sa_handler = read_handler;
    if (sigaction(SIGINT, &shell->sa, NULL) == -1)
        error_exit("sigaction");
}

void    heredoc_handler(int signum)
{
    (void)signum;
	g_signal = 1;
    printf("\nminishell ");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}
