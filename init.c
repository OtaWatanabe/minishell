/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:52:37 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/12 12:23:43 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	split_set(t_env *env, char *str)
{
	env->name = ft_substr(str, 0, ft_strchr(str, ':') - str);
	env->str = ft_strdup(ft_strchr(str, ':'));
	if (env->name == NULL || env->str == NULL)
	{
		perror("malloc");
		return (-1);
	}
	return (0);
}

int	set_path(t_shell *shell, char *str)
{
	size_t	i;

	shell->env_path = ft_split(str, ":");
	if (shell->env_path == NULL)
	{
		perror("malloc");
		return (-1);
	}
	i = 0;
	while (shell->env_path[i])
	{
		if ()
	}
}

void	init_env(t_shell *shell, char **env)
{
	t_env	*tmp;

	shell->env = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (shell->env == NULL)
	{
		perror("malloc");
		exit(1);
	}
	if (split_set(shell->env, *env) == -1)
		exit(1);
	tmp = shell->env;
	while (*++env)
	{
		tmp->next = ft_calloc(sizeof(t_env), 1);
		if (tmp->next == NULL)
		{
			perror("malloc");
			exit(1);
		}
		if (split_set(tmp->next, *env) == -1)
			exit(1);
		if (ft_strncmp(*env, "PATH", 5) == 0 && set_path(shell, tmp->next->str) == -1)
			exit(1);
		tmp = tmp->next;
	}
}

void	init_shell(t_shell *shell, char **env)
{
	if (*env)
		init_env(shell, env);
	shell->in_fd_dup = dup(0);
	shell->out_fd_dup = dup(1);
	if (shell->in_fd_dup == -1 || shell->out_fd_dup == -1)
	{
		perror("dup");
		exit(1);
	}
}
