/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:32:58 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/13 11:03:00 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	add_strlist(t_strlist **list, char *str)
{
	t_strlist	*new;
	t_strlist	*tmp;

	new = (t_strlist *)ft_calloc(sizeof(t_strlist), 1);
	if (new == NULL)
	{
		perror("malloc");
		return (-1);
	}
	new->str = str;
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

void	add_intlist(t_strlist **list, int n)
{
	t_intlist	*new;
	t_intlist	*tmp;

	new = (t_strlist *)ft_calloc(sizeof(t_strlist), 1);
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
