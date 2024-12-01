/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:52:14 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/12/01 16:23:53 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	command_error(char *command)
{
	ft_putstr_fd("mini: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

int	syntax_error(t_shell *shell, char *str)
{
	ft_putstr_fd("mini: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
	shell->exit_status = 258;
	return (-1);
}

void	error_exit(char *str)
{
	perror(str);
	exit(1);
}

int	ambiguous_error(t_shell *shell, char *str)
{
	ft_putstr_fd("mini: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("ambiguous redirect\n", 2);
	shell->exit_status = 1;
	return (-1);
}
