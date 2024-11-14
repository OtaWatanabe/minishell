/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:56:57 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/14 09:19:21 by otawatanabe      ###   ########.fr       */
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
		free_entire_list(commands->str_list);
		free(commands);
		commands = tmp;
	}
}

void	free_list_element(t_list *list)
{
	free(list->name);
	free(list->str);
	free(list);
}

void	free_entire_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free_list_element(tmp);
	}
}
