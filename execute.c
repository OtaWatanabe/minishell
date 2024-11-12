/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:48:04 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/12 10:45:42 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	command_execute(t_shell *shell, char **command, int if_last)
{
	char	*path;

	if (command == NULL)
		return ;
	if (!if_last && dup2(shell->pipe_fd[1], 1) == -1)
	{
		perror("dup2");
		exit(1);
	}
	built_in(shell, command);
	path = command_path(shell, *command);
	close(shell->pipe_fd[0]);
	close(shell->pipe_fd[1]);
	if (execve(path, command, shell->env) == -1)
	{
		ft_putstr_fd("mini: ", 2);
		perror(path);
		exit(127);
	}
}

int	mini_execute(t_shell *shell, t_command *commands, int fd)
{
	pid_t	p;
	char	**command;

	if (fd != -1 && dup2(fd, 0) == -1)
	{
		perror("dup2");
		return (-1);
	}
	command = remove_redirect(shell, commands);
	if (commands->next && pipe(shell->pipe_fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	p = fork();
	if (p == -1)
	{
		perror("fork");
		return (-1);
	}
	if (p == 0)
		command_execute(shell, command, commands->next == NULL);
	add_intlist(shell->pid, p);
	return (shell->pipe_fd[0]);
}

pid_t	wait_all(t_shell *shell)
{
	t_intlist	*tmp;
	int			*stat;

	tmp = shell->pid;
	while (tmp->next)
	{
		waitpid(tmp->num, stat, 0);
		tmp = tmp->next;
	}
	waitpid(tmp->num, stat, 0);
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
		if (reset_fd(shell) == -1)
			exit(1);
		commands = commands->next;
	}
	stat = ft_itoa(wait_all(shell));
	if (stat == NULL)
	{
		perror("malloc");
		exit(1);
	}
	if (env_set(shell, "?", stat) == -1)
		exit(1);
}
