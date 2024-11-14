/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:32:58 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/13 14:07:49 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	add_list(t_list **list, char *name, char *str, int num)
{
	t_list	*new;
	t_list	*tmp;

	new = (t_list *)ft_calloc(sizeof(t_list), 1);
	if (new == NULL)
	{
		perror("malloc");
		exit(1);
	}
	new->str = str;
	new->name = name;
	new->num = num;
	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	add_intlist(t_list **list, int n)
{
	t_list	*new;
	t_list	*tmp;

	new = (t_list *)ft_calloc(sizeof(t_list), 1);
	if (new == NULL)
	{
		perror("malloc");
		exit(1);
	}
	new->num = n;
	if (*list == NULL)
	{
		*list = new;
		return (0);
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
