/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:52:37 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/18 11:29:39 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	copy_str_array(char **from, char **to)
{
	if (from == NULL)
		return ;
	while (*from)
	{
		*to = error_strdup(*from);
		++to;
		++from;
	}
}

void	init_env_array(t_shell *shell, char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0 && env[i][4] == '=')
			set_path(shell, ft_strchr(env[i], '=') + 1);
		++i;
	}
	shell->env_array = (char **)ft_calloc(sizeof(char *) * (i + 1), 1);
	if (shell->env_array == NULL)
		error_exit("malloc");
	copy_str_array(env, shell->env_array);
}

void	init_shell(t_shell *shell, char **env)
{
	ft_memset(shell, 0, sizeof(t_shell));
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		error_exit("signal");
	init_sigaction(shell);
	if (*env)
		init_env_array(shell, env);
	shell->in_fd_dup = dup(0);
	shell->out_fd_dup = dup(1);
	if (shell->in_fd_dup == -1 || shell->out_fd_dup == -1)
		error_exit("dup");
}
