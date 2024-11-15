/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:52:37 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/15 15:11:49 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	init_env_list(t_shell *shell, char **env)
{
	t_mlist	*tmp;

	shell->env_list = (t_mlist *)ft_calloc(sizeof(t_mlist), 1);
	if (shell->env_list == NULL)
		error_exit("malloc");
	split_env(shell->env_list, *env);
	tmp = shell->env_list;
	if (ft_strncmp(*env, "PATH=", 5) == 0)
		set_path(shell, ft_strchr(*env, '=') + 1);
	while (*++env)
	{
		tmp->next = ft_calloc(sizeof(t_mlist), 1);
		if (tmp->next == NULL)
			error_exit("malloc");
		split_env(tmp->next, *env);
		if (ft_strncmp(*env, "PATH=", 5) == 0)
			set_path(shell, tmp->next->str);
		tmp = tmp->next;
	}
}

void	copy_str_array(char **from, char **to)
{
	while (*from)
	{
		*to = ft_strdup(*from);
		if (*to == NULL)
			error_exit("malloc");
		++to;
		++from;
	}
}

void	init_env_array(t_shell *shell, char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		++i;
	shell->env_array = (char **)ft_calloc(sizeof(char *) * (i + 1), 1);
	if (shell->env_array == NULL)
		error_exit("malloc");
	copy_str_array(env, shell->env_array);
}

void	init_shell(t_shell *shell, char **env)
{
	ft_memset(shell, 0, sizeof(t_shell));
	if (*env)
	{
		init_env_list(shell, env);
		init_env_array(shell, env);
	}
	shell->in_fd_dup = dup(0);
	shell->out_fd_dup = dup(1);
	if (shell->in_fd_dup == -1 || shell->out_fd_dup == -1)
		error_exit("dup");
}
