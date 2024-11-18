/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:28:01 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/18 14:28:01 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	ft_export(t_shell *shell, char **command)
{
	char	*tmp;

	printf("export\n");
	while (*command)
	{
		tmp = ft_strchr(*command, '=');
		if (tmp == *command)
		{
			ft_putstr_fd("mini: export: `", 2);
			ft_putstr_fd(tmp, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (1);
		}
		if (tmp)
		{
			*tmp = '\0';
			set_env(shell, *command, tmp + 1);
			printf("set: %s %s\n", *command, tmp + 1);
		}
		++command;
	}
	return (0);
}
