/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:36:12 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/16 11:05:44 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	close_files(t_shell *shell)
{
	t_mlist	*tmp;

	while (shell->open_fd)
	{
		close(shell->open_fd->num);
		tmp = shell->open_fd->next;
		free(shell->open_fd);
		shell->open_fd = tmp;
	}
}

void	delete_files(t_shell *shell)
{
	t_mlist	*tmp;

	while (shell->tmpfile)
	{
		tmp = shell->tmpfile;
		shell->tmpfile = tmp->next;
		unlink(tmp->name);
		free(tmp->name);
		free(tmp);
	}
}
