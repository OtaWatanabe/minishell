/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:44:18 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/16 14:19:40 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*add_env(t_shell *shell, char *command)
{
	char	*path;
	char	**env_path;

	if (shell->env_path == NULL)
		return (command);
	env_path = shell->env_path;
	while (*env_path)
	{
		path = ft_strjoin(*env_path, command);
		if (access(path, F_OK) == 0)
		{
			if (access(path, X_OK) == -1)
			{
				perror(command);
				exit(126);
			}
			return (path);
		}
		free(path);
		++env_path;
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
	if (ft_strchr(command, '/') == NULL && shell->env_path)
		return (add_env(shell, command));
	if (access(command, F_OK) == -1)
	{
		perror(command);
		exit(127);
	}
	if (access(command, X_OK) == -1)
	{
		perror(command);
		exit(126);
	}
	return (command);
}
