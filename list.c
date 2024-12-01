/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:32:58 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/12/01 14:10:47 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	**list_to_array(t_mlist *list)
{
	char	**ret;
	t_mlist	*tmp;
	size_t	i;

	i = 0;
	tmp = list;
	while (tmp)
	{
		++i;
		tmp = tmp->next;
	}
	ret = (char **)ft_calloc(sizeof(char *) * (i + 1), 1);
	if (ret == NULL)
		error_exit("malloc");
	tmp = list;
	i = 0;
	while (tmp)
	{
		ret[i++] = error_strdup(tmp->name);
		tmp = tmp->next;
	}
	return (ret);
}

void	add_list(t_mlist **list, char *name, char *str, int num)
{
	t_mlist	*new;
	t_mlist	*tmp;

	new = (t_mlist *)ft_calloc(sizeof(t_mlist), 1);
	if (new == NULL)
		error_exit("malloc");
	new->str = error_strdup(str);
	new->name = error_strdup(name);
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
