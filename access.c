/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:44:18 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/11 11:06:43 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

// int	r_access_open(t_pipex *pipex)
// {
// 	int	fd;

// 	if (access(pipex->input, F_OK) == -1)
// 	{
// 		existence_error(pipex->input);
// 		exit(0);
// 	}
// 	if (access(pipex->input, R_OK) == -1)
// 	{
// 		permission_error(pipex->input);
// 		exit(0);
// 	}
// 	fd = open(pipex->input, O_RDONLY);
// 	if (fd == -1)
// 		error_exit("open", pipex);
// 	return (fd);
// }

// int	w_access_open(t_pipex *pipex)
// {
// 	int	fd;

// 	if (access(pipex->output, F_OK) != -1 && access(pipex->output, W_OK) == -1)
// 	{
// 		permission_error(pipex->output);
// 		exit(0);
// 	}
// 	if (ft_strncmp(pipex->input, "here_doc", 9) == 0)
// 		fd = open(pipex->output, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	else
// 		fd = open(pipex->output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 		error_exit("open", pipex);
// 	return (fd);
// }

char	*concat_path(char *path, char *file, t_shell *shell)
{
	char	*concat;
	size_t	path_len;
	size_t	file_len;

	(void)shell;
	path_len = ft_strlen(path);
	file_len = ft_strlen(file);
	concat = ft_calloc(path_len + file_len + 2, 1);
	if (concat == NULL)
	{
		perror("malloc");
		exit(1);
	}
	ft_strlcpy(concat, path, path_len + 1);
	concat[path_len] = '/';
	ft_strlcat(concat, file, path_len + file_len + 2);
	return (concat);
}

char	*add_env(t_shell *shell, char *command)
{
	char		*path;
	t_strlist	*env_path;

	if (shell->env_path == NULL)
	{
		existence_error(command);
		exit(127);
	}
	env_path = shell->env_path;
	while (env_path)
	{
		path = ft_strjoin(env_path->str, command);
		if (access(path, F_OK) != -1)
			return (path);
		free(path);
		env_path = env_path->next;
	}
	command_error(command);
	exit(127);
}

char	*command_path(t_shell *shell, char *command)
{
	if (command[0] == '\0')
	{
		command_error("");
		exit(127);
	}
	if (ft_strchr(command, '/') == NULL)
		return (add_env(shell, command));
	return (command);
}
