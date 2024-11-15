/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:56:57 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/15 09:35:33 by otawatanabe      ###   ########.fr       */
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

	if (commands == NULL)
		return ;
	while (commands)
	{
		tmp = commands->next;
		free_entire_list(commands->redirect);
		free_char_array(commands->command);
		free(commands);
		commands = tmp;
	}
}

void	free_list_element(t_mlist *list)
{
	free(list->name);
	free(list->str);
	free(list);
}

void	free_entire_list(t_mlist *list)
{
	t_mlist	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free_list_element(tmp);
	}
}

void	free_shell(t_shell *shell)
{
	free_char_array(shell->env_path);
	free_char_array(shell->env_array);
	free_entire_list(shell->env_list);
}
