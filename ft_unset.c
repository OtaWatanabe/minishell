/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owatanab <owatanab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:28:06 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/18 17:35:24 by owatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	delete_words(char **env_array, char *str, int len)
{
	int	i;

	i = 0;
	while (env_array[i] != NULL)
	{
		if (strncmp(env_array[i], str, len) == 0)
		{
			free(env_array[i]);
			env_array[i] = strdup("");
			if (env_array[i] == NULL)
				error_exit("malloc:");
			break ;
		}
		i++;
	}
	return (0);
}

void	delete_env_path(char **env_path)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (env_path[count] != NULL)
		count++;
	while (i < count)
	{
		free(env_path[i]);
		i++;
	}
}

int	ft_unset(t_shell *shell, char **command)
{
	int	i;

	i = 1;
	while (command[i] != NULL)
	{
		delete_words(shell->env_array, command[i], strlen(command[i]));
		if (strncmp(command[i], "PATH", 5) == 0)
		{
			delete_env_path(shell->env_path);
			shell->env_path = NULL;
		}
		i++;
	}
	return (0);
}
