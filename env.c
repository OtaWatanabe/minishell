/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:26:47 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/12 10:42:08 by otawatanabe      ###   ########.fr       */
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
