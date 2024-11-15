/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:36:12 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/15 16:44:15 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	close_files(t_shell *shell)
{
	t_mlist	*tmp;

	close(shell->pipe_fd[0]);
	close(shell->pipe_fd[1]);
	while (shell->open_fd)
	{
		close(shell->open_fd->num);
		tmp = shell->open_fd->next;
		free(tmp);
		shell->open_fd = tmp;
	}
}

void	reset_fd(t_shell *shell)
{
	if ((dup2(shell->in_fd_dup, 0) == -1) || dup2(shell->out_fd_dup, 1) == -1)
		error_exit("malloc");
}

int	create_file(char *filename)
{
	int	fd;

	if (filename == NULL)
		return (-1);
	fd = open(filename, O_WRONLY | O_CREAT, 0777);
	if (fd == -1)
	{
		free(filename);
		perror("open");
		return (-1);
	}
	return (0);
}

void	push_fd(t_shell *shell, int fd, char *file)
{
	if (file)
		add_list(&shell->tmpfile, file, NULL, 0);
	add_list(&shell->open_fd, NULL, NULL, fd);
}
