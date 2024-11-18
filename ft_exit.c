/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:27:58 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/18 16:09:59 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	check_numeric(char *str)
{
	if (*str == '-')
		++str;
	if (*str == '\0')
		return (0);
	while ('0' <= *str && *str <= '9')
		++str;
	if (*str)
		return (0);
	return (1);
}

int	check_status(char **commands)
{
	int	i;

	i = 1;
	if (commands[i] == NULL)
		return (0);
	while (commands[i] != NULL)
		i++;
	if (check_numeric(commands[1]) == 0)
		return (255);
	if (i == 2)
		return (ft_atoi(commands[1]) % 256);
	return (300);
}

int	ft_exit(t_shell *shell, char **commands)
{
	int	exit_status;

	exit_status = check_status(commands);
	if (exit_status == 300)
	{
		ft_putstr_fd("mini: exit: too many arguments\n", 2);
		return (1);
	}
	if (shell->if_pipe == 0)
		ft_putstr_fd("exit\n", 2);
	if (exit_status == 255)
		ft_putstr_fd("bash: exit: numeric argument required\n", 2);
	if (shell->if_pipe)
		return (exit_status);
	exit(exit_status);
}
