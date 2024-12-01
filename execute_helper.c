/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:45:05 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/12/01 17:25:52 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	set_fd(t_shell *shell, t_command *command)
{
	if (command->next)
	{
		if (dup2(shell->pipe_fd[1], 1) == -1)
			error_exit("dup2");
		close(shell->pipe_fd[1]);
	}
	if (command->in_fd != 0 && dup2(command->in_fd, 0) == -1)
		error_exit("dup2");
	if (command->out_fd != 1 && dup2(command->out_fd, 1) == -1)
		error_exit("dup2");
	if (command->in_fd != 0)
		close(command->in_fd);
	if (command->out_fd != 1)
		close(command->out_fd);
}

void	reset(t_shell *shell)
{
	free_entire_list(shell->pid);
	shell->pid = NULL;
	delete_files(shell);
	if (dup2(shell->in_fd_dup, 0) == -1 || dup2(shell->out_fd_dup, 1) == -1)
		error_exit("dup2");
	if (g_signal == 1)
		shell->exit_status = 1;
	if (g_signal == 2)
	{
		shell->exit_status = 130;
		ft_putstr_fd("\n", 2);
	}
	if (g_signal == 3)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		shell->exit_status = 131;
	}
	g_signal = 0;
	free_commands(shell->commands);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		error_exit("signal");
}
