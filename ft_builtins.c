/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:26:12 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/18 14:42:05 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

/*
    前提としてdupとパイプでの出力処理はうまくいってるとし、
    こちらではエラー処理は書いていない。
*/

int	built_in(t_shell *shell, char **command)
{
	if (command[0] == NULL)
		return (-1);
	if (strncmp("echo", command[0], 5) == 0)
		return (ft_echo(command));
	else if (strncmp("cd", command[0], 3) == 0)
		return (ft_cd(shell, command));
	else if (strncmp("pwd", command[0], 4) == 0)
		return (ft_pwd());
	else if (strncmp("export", command[0], 7) == 0)
		return (ft_export(shell, command));
	else if (strncmp("unset", command[0], 6) == 0)
		return (ft_unset(shell, command));
	else if (strncmp("env", command[0], 4) == 0)
		return (ft_env(shell));
	else if (strncmp("exit", command[0], 5) == 0)
		return (ft_exit(shell, command));
	return (-1);
}
