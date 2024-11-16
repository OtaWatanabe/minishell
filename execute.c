/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:48:04 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/16 14:24:31 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	command_execute(t_shell *shell, t_command *command)
{
	char	*path;

	if (*command->command == NULL)
		exit(0);
	if (command->next)
	{
		if (dup2(shell->pipe_fd[1], 1) == -1)
			error_exit("dup2");
		close(shell->pipe_fd[0]);
		close(shell->pipe_fd[1]);
	}
	if (command->in_fd != 0 && dup2(command->in_fd, 0) == -1)
		error_exit("dup2");
	if (command->out_fd != 1 && dup2(command->out_fd, 1) == -1)
		error_exit("dup2");
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

	if (commands->in_fd == -1 || commands->out_fd == -1)
		return (-1);
	if (commands->next && pipe(shell->pipe_fd) == -1)
		error_exit("pipe");
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

pid_t	wait_all(t_shell *shell, int error)
{
	t_mlist	*tmp;
	int		stat;

	if (shell->pid == NULL)
		return (0);
	tmp = shell->pid;
	while (tmp->next)
	{
		waitpid(tmp->num, &stat, 0);
		tmp = tmp->next;
	}
	waitpid(tmp->num, &stat, 0);
	if (error == -1)
		return (1);
	return (WEXITSTATUS(stat));
}

void	reset(t_shell *shell)
{
	free_entire_list(shell->pid);
	shell->pid = NULL;
	delete_files(shell);
	if (dup2(shell->in_fd_dup, 0) == -1)
		error_exit("dup2");
}

void	pipe_all(t_shell *shell)
{
	t_command	*commands;
	int			error;

	commands = shell->commands;
	if (commands == NULL)
		return ;
	redirect_all(shell);
	while (commands)
	{
		error = mini_execute(shell, commands);
		if (commands->next)
		{
			if (dup2(shell->pipe_fd[0], 0) == -1)
				error_exit("dup2");
			close(shell->pipe_fd[0]);
			close(shell->pipe_fd[1]);
		}
		commands = commands->next;
	}
	shell->exit_status = wait_all(shell, error);
	reset(shell);
}
