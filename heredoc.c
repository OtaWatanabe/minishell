/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owatanab <owatanab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:20:12 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/16 18:32:46 by owatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*get_random(size_t n)
{
	char	*ret;
	size_t	i;

	ret = ft_calloc(n + 14, 1);
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

char	*get_filename(void)
{
	char	*random;
	size_t	i;

	random = get_random(0);
	i = 1;
	while (access(random, F_OK) == 0)
	{
		free(random);
		random = get_random(i);
		++i;
	}
	return (random);
}

char	*h_extract_env(t_shell *shell, char *str)
{
	char	*env_str;
	char	*tmp;
	char	*ret;
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\'' && str[i] != '\"' && str[i] != ':')
		++i;
	tmp = ft_substr(str, 0, i);
	if (tmp == NULL)
		error_exit("malloc");
	env_str = get_env(shell, tmp);
	free(tmp);
	tmp = h_expand_env(shell, str + i);
	ret = ft_strjoin(env_str, tmp);
	free(tmp);
	free(env_str);
	if (ret == NULL)
		error_exit("malloc");
	return (ret);
}

char	*h_expand_env(t_shell *shell, char *str)
{
	char	*ret;
	char	*tmp;
	char	*tmp1;

	tmp = ft_strchr(str, '$');
	while (tmp && (tmp[1] == '\'' || tmp[1] == '\"' || tmp[1] == ':' || !tmp[1]))
		tmp = ft_strchr(tmp + 1, '$');
	if (tmp)
	{
		tmp1 = ft_substr(str, 0, tmp - str);
		if (tmp1 == NULL)
			error_exit("malloc");
		tmp = h_extract_env(shell, tmp + 1);
		ret = ft_strjoin(tmp1, tmp);
		free(tmp1);
		free(tmp);
		return (ret);
	}
	ret = ft_strdup(str);
	if (ret == NULL)
		error_exit("malloc");
	return (ret);
}

void	read_doc(t_shell *shell, int fd, char *eof)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = readline("> ");
		tmp = line;
		if (line == NULL || ft_strncmp(line, eof, ft_strlen(eof) + 1) == 0)
		{
			close(fd);
			free(line);
			return ;
		}
		line = h_expand_env(shell, line);
		free(tmp);
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
		error_exit("malloc");
	}
	if (dup2(fd, 0) == -1)
	{
		close(fd);
		unlink(filename);
		error_exit("dup2");
	}
	return (fd);
}

int	here_doc(t_shell *shell, t_mlist *here)
{
	int		fd;
	char	*filename;

	shell->sa.sa_handler = heredoc_handler;
	if (sigaction(SIGINT, &shell->sa, NULL) == -1)
        error_exit("sigaction");
	filename = get_filename();
	if (dup2(shell->in_fd_dup, 0) == -1 || dup2(shell->out_fd_dup, 1) == -1)
		error_exit("dup2");
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		error_exit("open");
	read_doc(shell, fd, here->name);
	here = here->next;
	fd = open_dup(filename);
	add_list(&shell->tmpfile, filename, NULL, 0);
	free(filename);
	shell->sa.sa_handler = parent;
	if (sigaction(SIGINT, &shell->sa, NULL) == -1)
    	error_exit("sigaction");
	return (fd);
}
