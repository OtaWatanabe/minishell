/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:48:04 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/12/01 17:20:33 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	command_execute(t_shell *shell, t_command *command)
{
	char	*path;

	if (command->next)
		close(shell->pipe_fd[0]);
	init_sigaction(shell);
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		error_exit("signal");
	if (*command->command == NULL)
		exit(0);
	path = command_path(shell, command->command[0]);
	if (execve(path, command->command, shell->env_array) == -1)
	{
		ft_putstr_fd("mini: ", 2);
		perror(path);
		exit(128);
	}
}

int	mini_execute(t_shell *shell, t_command *commands)
{
	pid_t	p;
	int		status;

	if (commands->in_fd == -1 || commands->out_fd == -1 || g_signal)
		return (-1);
	if (commands->next && pipe(shell->pipe_fd) == -1)
		error_exit("pipe");
	set_fd(shell, commands);
	status = built_in(shell, commands->command);
	if (status != -1)
		return (status + 1);
	p = fork();
	if (p == -1)
		error_exit("fork");
	if (p == 0)
		command_execute(shell, commands);
	add_list(&shell->pid, NULL, NULL, p);
	if (commands->in_fd != 0)
		close(commands->in_fd);
	if (commands->out_fd != 1)
		close(commands->out_fd);
	return (0);
}

pid_t	wait_all(t_shell *shell, int status)
{
	t_mlist	*tmp;
	int		stat;

	tmp = shell->pid;
	while (tmp)
	{
		waitpid(tmp->num, &stat, 0);
		if (errno == EINTR)
			continue ;
		tmp = tmp->next;
	}
	if (status == -1)
		return (1);
	if (0 < status)
		return (status - 1);
	return (WEXITSTATUS(stat));
}

int	pipe_all(t_shell *shell)
{
	t_command	*commands;
	int			status;

	shell->sa.sa_handler = parent;
	if (sigaction(SIGINT, &shell->sa, NULL) == -1 || sigaction(SIGQUIT,
			&shell->sa, NULL) == -1)
		error_exit("sigaction");
	commands = shell->commands;
	while (commands)
	{
		status = mini_execute(shell, commands);
		if (dup2(shell->out_fd_dup, 1) == -1)
			error_exit("dup2");
		if (commands->next)
		{
			if (dup2(shell->pipe_fd[0], 0) == -1)
				error_exit("dup2");
			close(shell->pipe_fd[0]);
		}
		else if (dup2(shell->in_fd_dup, 0) == -1)
			error_exit("dup2");
		commands = commands->next;
	}
	return (status);
}

void	execute_all(t_shell *shell)
{
	int	status;

	if (shell->commands == NULL)
		return ;
	redirect_all(shell);
	if (g_signal)
	{
		reset(shell);
		return ;
	}
	status = pipe_all(shell);
	shell->exit_status = wait_all(shell, status);
	reset(shell);
}
