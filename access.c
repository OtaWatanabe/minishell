/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:44:18 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/13 11:17:43 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*add_env(t_shell *shell, char *command)
{
	char		*path;
	t_strlist	*env_path;

	if (shell->env_path == NULL)
		return (command);
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
