/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:52:37 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/13 10:52:41 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

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
