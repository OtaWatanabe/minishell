/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:35:42 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/12/01 14:04:08 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

t_mlist	*expand_str(t_shell *shell, t_mlist *list)
{
	char	*before;
	t_mlist	*tmp;
	t_mlist	*tmp1;

	before = list->name;
	if (list->str == NULL || ft_strncmp(list->str, "<<", 3))
		list->name = expand_env(shell, before, 0);
	tmp1 = list->next;
	tmp = expand_split(list);
	tmp->next = tmp1;
	if (list->str && (tmp != list || tmp->name == NULL))
	{
		ambiguous_error(shell, before);
		free(before);
		return (NULL);
	}
	if (list->str == NULL || ft_strncmp(list->str, "<<", 3))
		free(before);
	return (tmp);
}

int	expand_list(t_shell *shell, t_mlist **list)
{
	t_mlist	*tmp;

	tmp = *list;
	while (tmp)
	{
		tmp = expand_str(shell, tmp);
		if (tmp == NULL)
			return (-1);
		tmp = tmp->next;
	}
	skip_null(list);
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
		if ((*tmp != '\'' && *tmp != '\"') || (*tmp == '\'' && quote == 2)
			|| (*tmp == '\"' && quote == 1))
			str_list->name[i++] = *tmp;
		quote = get_quote_status(quote, *tmp);
		++tmp;
	}
	free(for_free);
	return (str_list);
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
	size_t	i;

	i = 0;
	if (*str == '?')
		return (free_strjoin(ft_itoa(shell->exit_status), expand_env(shell, str + 2, quote)));
	while (str[i] && str[i] != '\'' && str[i] != '\"' && str[i] != ':'
		&& str[i] != '$' && str[i] != '?')
		++i;
	tmp = ft_substr(str, 0, i);
	if (tmp == NULL)
		error_exit("malloc");
	env_str = get_env(shell, tmp);
	free(tmp);
	return (free_strjoin(env_str, expand_env(shell, str + i, quote)));
}
