/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:20:12 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/18 17:04:44 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

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
	while (str[i] && str[i] != '\'' && str[i] != '\"' && str[i] != ':'
		&& str[i] != ' ')
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
	while (tmp && (tmp[1] == '\'' || tmp[1] == '\"' || tmp[1] == ':' || !tmp[1]
			|| tmp[1] == ' '))
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

void	read_doc(t_shell *shell, char *filename, char *eof)
{
	char	*tmp;
	int		fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		error_exit("open");
	while (1)
	{
		shell->input = readline("> ");
		if (g_signal)
			return ;
		tmp = shell->input;
		if (tmp == NULL || ft_strncmp(tmp, eof, ft_strlen(eof) + 1) == 0)
		{
			close(fd);
			free(tmp);
			shell->input = NULL;
			return ;
		}
		tmp = h_expand_env(shell, tmp);
		free(shell->input);
		ft_putendl_fd(tmp, fd);
		free(tmp);
	}
}

int	here_doc(t_shell *shell, t_mlist *here)
{
	int		fd;
	char	*filename;

	filename = get_filename();
	if (dup2(shell->in_fd_dup, 0) == -1 || dup2(shell->out_fd_dup, 1) == -1)
		error_exit("dup2");
	read_doc(shell, filename, here->name);
	if (g_signal)
	{
		free(filename);
		return (-1);
	}
	here = here->next;
	fd = open_dup(filename);
	add_list(&shell->tmpfile, filename, NULL, 0);
	free(filename);
	return (fd);
}
