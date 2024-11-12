/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:56:57 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/11 11:02:27 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	free_char_array(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return ;
	while (array[i])
	{
		free(array[i]);
		++i;
	}
	free(array);
}

void	free_commands(t_command *commands)
{
	t_command	*tmp;

	while (commands)
	{
		tmp = commands->next;
		free_char_array(commands->command);
		free(commands);
		commands = tmp;
	}
}

void	free_path(t_strlist *path)
{
	t_strlist	*tmp;

	while (path)
	{
		tmp = path->next;
		free(path->str);
		free(path);
		path = tmp;
	}
}
