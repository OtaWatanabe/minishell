/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:26:47 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/13 10:52:48 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	set_env(t_shell *shell, char *name, char *str)
{
	t_env	*tmp;
	t_env	*new;

	tmp = shell->env;
	while (tmp && tmp->next && ft_strncmp(tmp->name, name, ft_strlen(name) + 1))
		tmp = tmp->next;
	if (tmp && ft_strncmp(tmp->name, name, ft_strlen(name) + 1) == 0)
	{
		tmp->str = str;
		return (0);
	}
	new = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (new == NULL)
	{
		perror("malloc");
		return (-1);
	}
	if (tmp == NULL)
	{
		shell->env = new;
		return (0);
	}
	tmp->next = new;
	return (0);
}

void	split_set(t_env *env, char *str)
{
	env->name = ft_substr(str, 0, ft_strchr(str, '=') - str);
	env->str = ft_strdup(ft_strchr(str, '=') + 1);
	if (env->name == NULL || env->str == NULL)
	{
		perror("malloc");
		exit(1);
	}
}

void	set_path(t_shell *shell, char *str)
{
	size_t	i;
	char	*tmp;

	shell->env_path = ft_split(str, ":");
	if (shell->env_path == NULL)
	{
		perror("malloc");
		exit(1);
	}
	i = 0;
	while (shell->env_path[i])
	{
		if (shell->env_path[i][ft_strlen(shell->env_path[i]) - 1] != '/')
		{
			tmp = shell->env_path[i];
			shell->env_path[i] = ft_strjoin(shell->env_path[i], "/");
			free(tmp);
			if (shell->env_path[i])
			{
				perror("malloc");
				exit(1);
			}
		}
		++i;
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
	split_set(shell->env, *env);
	tmp = shell->env;
	while (*++env)
	{
		tmp->next = ft_calloc(sizeof(t_env), 1);
		if (tmp->next == NULL)
		{
			perror("malloc");
			exit(1);
		}
		split_set(tmp->next, *env);
		if (ft_strncmp(*env, "PATH", 5) == 0)
			set_path(shell, tmp->next->str);
		tmp = tmp->next;
	}
}
