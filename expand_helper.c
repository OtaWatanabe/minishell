/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:38:41 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/18 16:55:57 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

size_t	get_head_len(char *str)
{
	int		quote;
	size_t	i;
	size_t	len;

	i = 0;
	quote = 0;
	len = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = (str[i] == '\'') + (str[i] == '\"') * 2;
		else if ((quote == 1 && str[i] == '\'') || (quote == 2
				&& str[i] == '\"'))
			quote = 0;
		else if (!quote && str[i] == ' ')
			return (len);
		else
			++len;
		++i;
	}
	return (len);
}

char	*skip_space(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] == ' ')
		++i;
	return (str + i);
}

char	*set_next(t_mlist **str_list, char *str, int if_first)
{
	str = skip_space(str);
	if (*str == '\0' && if_first)
	{
		(*str_list)->name = NULL;
		return (NULL);
	}
	else if (*str == '\0')
		return (NULL);
	if (!if_first)
	{
		(*str_list)->next = (t_mlist *)ft_calloc(sizeof(t_mlist), 1);
		if ((*str_list)->next == NULL)
			error_exit("malloc");
		*str_list = (*str_list)->next;
	}
	(*str_list)->name = (char *)ft_calloc(get_head_len(str) + 1, 1);
	if ((*str_list)->name == NULL)
		error_exit("malloc");
	return (str);
}

void	skip_null(t_mlist **list)
{
	t_mlist	*tmp;
	t_mlist	*tmp1;

	while (*list && (*list)->name == NULL)
	{
		tmp = (*list)->next;
		free(*list);
		*list = tmp;
	}
	if (*list == NULL)
		return ;
	tmp1 = *list;
	while (tmp1->next)
	{
		tmp = tmp1->next;
		if (tmp->name == NULL)
		{
			tmp1->next = tmp->next;
			free(tmp);
		}
		else
			tmp1 = tmp1->next;
	}
}

int	get_quote_status(int quote, char c)
{
	if (!quote && (c == '\'' || c == '\"'))
		return ((c == '\'') + (c == '\"') * 2);
	if ((quote == 1 && c == '\'') || (quote == 2 && c == '\"'))
		return (0);
	return (quote);
}
