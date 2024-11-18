/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:15:27 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/18 16:43:18 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	get_input(t_shell *shell)
{
	shell->sa.sa_handler = read_handler;
	if (sigaction(SIGINT, &shell->sa, NULL) == -1)
		error_exit("sigaction");
	if (shell->input)
		return ;
	shell->input = readline("minishell > ");
	if (shell->input == NULL)
		return ;
	while (*shell->input == '\0')
	{
		free(shell->input);
		shell->input = readline("minishell > ");
		if (shell->input == NULL)
			return ;
	}
	add_history(shell->input);
	if (g_signal)
	{
		g_signal = 0;
		shell->exit_status = 1;
	}
}
