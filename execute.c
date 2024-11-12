/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:48:04 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/21 20:30:02 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	command_execute(t_shell *shell, char **command, int if_last)
{
	char	*path;

	if (!if_last && dup2(0, shell->pipe_fd[1]) == -1)
	{
		perror("dup2 error\n");
		exit(1);
	}
	path = command_path(shell, *command);
	close(shell->pipe_fd[0]);
	close(shell->pipe_fd[1]);
	if (execve(path, command, shell->env) == -1)
	{
		ft_putstr_fd("bash: ", 2);
		perror(path);
		exit(127);
	}
}

int	mini_execute(t_shell *shell, t_command *commands, int fd)
{
	pid_t	p;
	char	**command;

	if (fd != -1 && dup2(0, fd) == -1)
	{
		perror("dup2 error");
		return (-1);
	}
	command = extract_redirect(shell, commands);
	if (commands == NULL)
		return (-1);
	if (!commands->if_last && pipe(shell->pipe_fd) == -1)
	{
		perror("pipe error");
		return (-1);
	}
	p = 0;
	if (p == -1)
	{
		perror("fork error");
		return (-1);
	}
	if (p == 0)
		command_execute(shell, command, commands->if_last);
	return (shell->pipe_fd[1]);
}

void	pipe_all(t_shell *shell)
{
	int			fd;
	t_command	*commands;

	commands = shell->commands;
	fd = -1;
	while (commands)
	{
		fd = mini_execute(shell, commands, fd);
		close_files(shell);
		reset_fd(shell);
		commands = commands->next;
	}
}
