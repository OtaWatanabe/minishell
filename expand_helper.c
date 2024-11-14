/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:38:41 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/14 10:50:51 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

size_t	get_head_len(char *str)
{
	int	quote;
	size_t	i;
	size_t	len;

	i = 0;
	quote = 0;
	len = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = (str[i] == '\'') + (str[i] == '\"') * 2;
		else if ((quote == 1 && str[i] == '\'') || (quote == 2 && str[i] == '\"'))
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
	int		quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (!quote && (str[i] == '\'' || str[i] == '\"'))
			quote = (str[i] == '\'' || str[i] == '\"');
		else if ((quote == 1 && str[i] == '\'') || (quote == 2 && str[i] == '\"'))
			quote = 0;
		else if (quote)
			return (str + i - 1);
		else if (str[i] != ' ' && !quote)
			return (str + i);
		++i;
	}
	return (NULL);
}

char	*set_next(t_list **str_list, char *str, int if_first)
{
	str = skip_space(str);
	if (str == NULL && if_first)
	{
		(*str_list)->name = NULL;
		return (NULL);
	}
	else if (str == NULL)
		return (NULL);
	if (!if_first)
	{
		(*str_list)->next = (t_list *)ft_calloc(sizeof(t_list), 1);
		if ((*str_list)->next == NULL)
			error_exit("malloc");
		*str_list = (*str_list)->next;
	}
	(*str_list)->name = (char *)ft_calloc(get_head_len(str), 1);
	if ((*str_list)->name == NULL)
		error_exit("malloc");
	return (str);
}

void	skip_null(t_list **list)
{
	t_list	*tmp;
	t_list	*tmp1;

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

int	check_redirect_syntax(t_list *list)
{
	if (list == NULL)
		return (0);
	while (list->next)
	{
		if (list->next->num == 1 && list->num == 1)
		{
			syntax_error(list->next->name);
			return (-1);
		}
		list = list->next;
	}
	return (0);
}
