/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owatanab <owatanab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:35:42 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/16 16:10:47 by owatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

t_mlist	*expand_str(t_shell *shell, t_mlist *list, int if_redirect)
{
	char	*before;
	t_mlist	*tmp;
	t_mlist	*tmp1;

	before = list->name;
	if (list->str == NULL || ft_strncmp(list->str, "<<", 3))
		list->name = expand_env(shell, before, 0);
	tmp = list;
	tmp1 = tmp->next;
	tmp = expand_split(tmp);
	tmp->next = tmp1;
	if (if_redirect && (tmp != list || tmp->name == NULL))
	{
		ambiguous_error(shell, before);
		free(before);
		return (NULL);
	}
	if (list->str == NULL || ft_strncmp(list->str, "<<", 3))
		free(before);
	return (tmp);
}

int	expand_list(t_shell *shell, t_mlist **list, int if_redirect)
{
	t_mlist	*tmp;

	tmp = *list;
	while (tmp)
	{
		tmp = expand_str(shell, tmp, if_redirect);
		if (tmp == NULL)
			return (-1);
		tmp = tmp->next;
	}
	skip_null(list);
	return (0);
}

int	expand_all(t_shell *shell, t_command *commands)
{
	t_command	*tmp;

	tmp = commands;
	while (tmp)
	{
		expand_list(shell, &tmp->tmp, 0);
		tmp->command = list_to_array(tmp->tmp);
		free_entire_list(tmp->tmp);
		tmp->tmp = NULL;
		if (expand_list(shell, &tmp->redirect, 1) == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}

t_mlist	*expand_split(t_mlist *str_list)
{
	int		quote;
	size_t	i;
	char	*tmp;
	char	*for_free;

	i = 0;
	for_free = str_list->name;
	tmp = set_next(&str_list, str_list->name, 1);
	quote = 0;
	while (tmp && *tmp)
	{
		if (!quote && *tmp == ' ')
		{
			tmp = set_next(&str_list, tmp, 0);
			i = 0;
			continue ;
		}
		if ((*tmp != '\'' && *tmp != '\"')
			|| (*tmp == '\'' && quote == 2) || (*tmp == '\"' && quote == 1))
			str_list->name[i++] = *tmp;
		quote = get_quote_status(quote, *tmp);
		++tmp;
	}
	free(for_free);
	return (str_list);
}

int get_quote_status(int quote, char c)
{
	if (!quote && (c == '\'' || c == '\"'))
		return ((c == '\'') + (c == '\"') * 2);
	if ((quote == 1 && c == '\'') || (quote == 2 && c == '\"'))
		return (0);
	return (quote);
}

char	*expand_env(t_shell *shell, char *str, int quote)
{
	size_t	i;
	char	*ret;
	char	*tmp;

	i = 0;
	while (str[i])
	{
		if (quote != 1 && str[i] == '$' && str[i + 1] != ':' && str[i + 1]
			&& (quote == 0 || (str[i + 1] != '\'' && str[i + 1] != '\"')))
		{
			str[i] = '\0';
			tmp = extract_env(shell, str + i + 1, quote);
			ret = ft_strjoin(str, tmp);
			free(tmp);
			if (ret == NULL)
				error_exit("malloc");
			return (ret);
		}
		quote = get_quote_status(quote, str[i++]);
	}
	return (error_strdup(str));
}

char	*extract_env(t_shell *shell, char *str, int quote)
{
	char	*env_str;
	char	*tmp;
	char	*ret;
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\'' && str[i] != '\"'
		&& str[i] != ':' && str[i] != '$')
		++i;
	tmp = ft_substr(str, 0, i);
	if (tmp == NULL)
		error_exit("malloc");
	env_str = get_env(shell, tmp);
	free(tmp);
	tmp = expand_env(shell, str + i, quote);
	ret = ft_strjoin(env_str, tmp);
	free(tmp);
	free(env_str);
	if (ret == NULL)
		error_exit("malloc");
	return (ret);
}
