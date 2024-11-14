/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:52:14 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/14 10:56:02 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	command_error(char *command)
{
	ft_putstr_fd("mini: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	syntax_error(char *str)
{
	ft_putstr_fd("bash: syntax error near unexpected token near `", 2);
	if (str)
		ft_putstr_fd(str, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
}

void	error_exit(char *str)
{
	perror(str);
	exit(1);
}
