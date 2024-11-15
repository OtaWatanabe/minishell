/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:32:27 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/15 18:18:02 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	split_env(t_mlist *env, char *str)
{
	env->name = ft_substr(str, 0, ft_strchr(str, '=') - str);
	env->str = ft_strdup(ft_strchr(str, '=') + 1);
	if (env->name == NULL || env->str == NULL)
		error_exit("malloc");
}

void	set_path(t_shell *shell, char *str)
{
	size_t	i;
	char	*tmp;

	shell->env_path = ft_split(str, ':');
	if (shell->env_path == NULL)
		error_exit("malloc");
	i = 0;
	while (shell->env_path[i])
	{
		if (shell->env_path[i][ft_strlen(shell->env_path[i]) - 1] != '/')
		{
			tmp = shell->env_path[i];
			shell->env_path[i] = ft_strjoin(shell->env_path[i], "/");
			free(tmp);
			if (shell->env_path[i] == NULL)
				error_exit("malloc");
		}
		++i;
	}
}
