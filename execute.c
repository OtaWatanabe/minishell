/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:48:04 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/15 18:40:53 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	command_execute(t_shell *shell, t_command *command)
{
	char	*path;

	if (command == NULL)
		exit(0);
	if (command->next)
	{
		if (dup2(shell->pipe_fd[1], 1) == -1)
			error_exit("dup2");
		close(shell->pipe_fd[0]);
		close(shell->pipe_fd[1]);
	}
	// built_in(shell, command);
	path = command_path(shell, command->command[0]);
	if (execve(path, command->command, shell->env_array) == -1)
	{
		ft_putstr_fd("mini: ", 2);
		perror(path);
		exit(127);
	}
}

int	mini_execute(t_shell *shell, t_command *commands, int fd)
{
	pid_t	p;

	if (fd != -1 && dup2(fd, 0) == -1)
		error_exit("dup2");
	redirect_all(shell, commands->redirect);
	if (commands->next && pipe(shell->pipe_fd) == -1)
		error_exit("pipe");
	p = fork();
	if (p == -1)
		error_exit("fork");
	if (p == 0)
		command_execute(shell, commands);
	add_list(&shell->pid, NULL, NULL, p);
	return (shell->pipe_fd[0]);
}

pid_t	wait_all(t_shell *shell)
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
	return (WEXITSTATUS(stat));
}

void	pipe_all(t_shell *shell)
{
	int			fd;
	char		*stat;
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
	stat = ft_itoa(wait_all(shell));
	if (stat == NULL)
		error_exit("malloc");
	set_env(shell, "?", stat);
	free(stat);
}
