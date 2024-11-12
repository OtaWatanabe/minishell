/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:36:12 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/21 20:34:11 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	close_files(t_shell *shell)
{
	t_fd	*open_file;
	t_fd	*tmp;

	close(shell->pipe_fd[0]);
	close(shell->pipe_fd[1]);
	open_file = shell->openfile;
	while (open_file)
	{
		close(open_file->fd);
		if (open_file->file)
			unlink(open_file->file);
		tmp = open_file;
		open_file = tmp->next;
		free(tmp);
	}
}

void	reset_fd(t_shell *shell)
{
	if (dup2(0, shell->in_fd_dup) == -1 || dup2(0, shell->out_fd_dup) == -1)
	{
		perror("dup2 error\n");
		exit(1);
	}
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
		perror("open error\n");
		return (-1);
	}
	return (0);
}
