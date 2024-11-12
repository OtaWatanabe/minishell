/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:20:12 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/11 09:49:36 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*get_random(int n)
{
	char	*ret;
	int		i;

	ret = ft_calloc(n + 14, 1);
	if (ret == NULL)
	{
		perror("malloc");
		return (NULL);
	}
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

char	*get_filename(void)
{
	char	*random;
	int		i;

	random = get_random(0);
	if (random == NULL)
		return (NULL);
	i = 1;
	while (access(random, F_OK) == 0)
	{
		free(random);
		random = get_random(i);
		if (random == NULL)
			return (NULL);
		++i;
	}
	return (random);
}

void	read_doc(int fd, char *eof)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (line == NULL || ft_strncmp(line, eof, ft_strlen(eof) + 1) == 0)
		{
			close(fd);
			free(line);
			return ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
}

int	open_dup(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		unlink(filename);
		free(filename);
		perror("open");
		return (-1);
	}
	if (dup2(fd, 0) == -1)
	{
		close(fd);
		unlink(filename);
		free(filename);
		perror("dup2");
		return (-1);
	}
	return (fd);
}

int	here_doc(t_shell *shell, char *eof)
{
	int		fd;
	char	*filename;

	if (dup2(shell->in_fd_dup, 0) == -1)
	{
		perror("dup2");
		return (-1);
	}
	filename = get_filename();
	fd = create_file(filename);
	if (fd == -1)
		return (-1);
	read_doc(fd, eof);
	fd = open_dup(filename);
	if (fd == -1)
		return (-1);
	if (push_fd(shell, fd, filename) == -1)
		return (-1);
	return (0);
}
