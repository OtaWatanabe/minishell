/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:04:03 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/12/01 14:49:41 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	open_dup(t_shell *shell, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		delete_files(shell);
		error_exit("malloc");
	}
	if (dup2(fd, 0) == -1)
	{
		close(fd);
		delete_files(shell);
		error_exit("dup2");
	}
	return (fd);
}

char	*get_random(size_t n)
{
	char	*ret;
	size_t	i;

	ret = (char *)ft_calloc(n + 14, 1);
	if (ret == NULL)
		error_exit("malloc");
	i = 0;
	while (i < 12)
	{
		ret[i] = "/tmp/tmpfile"[i];
		++i;
	}
	while (i - 12 < n)
	{
		ret[i] = '+';
		++i;
	}
	return (ret);
}
