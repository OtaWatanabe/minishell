/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:35:42 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/14 11:24:20 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	expand_command(t_shell *shell, t_command *commands)
{
	t_list	*tmp;
	t_list	*tmp1;
	char	*before;

	tmp = commands->str_list;
	while (tmp)
	{
		before = tmp->name;
		tmp->name = expand_env(shell, tmp->name, 0);
		free(before);
		tmp1 = tmp->next;
		tmp = expand_split(tmp);
		tmp->next = tmp1;
		tmp = tmp1;
	}
	skip_null(&commands->str_list);
	return (check_syntax(commands->str_list));
}

int	expand_all(t_shell *shell, t_command *commands)
{
	t_command	*tmp;

	tmp = commands;
	while (tmp)
	{
		if (expand_command(shell, tmp->str_list) == -1)
			return (-1);
		tmp = tmp->next;
	}
	tmp = commands;
	while (tmp)
	{
		if (tmp->str_list == NULL && tmp->next)
		{
			syntax_error("|");
			return (-1);
		}
		if (tmp->str_list == NULL)
		{
			syntax_error(NULL);
			return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}

t_list	*expand_split(t_list *str_list)
{
	int		quote;
	size_t	i;
	char	*tmp;
	char	*for_free;

	i = 0;
	for_free = str_list->name;
	tmp = set_next(&str_list, str_list->name, 1);
	while (tmp && *tmp)
	{
		if (!quote && *tmp == ' ')
		{
			tmp = set_next(&str_list, tmp, 0);
			i = 0;
			continue ;
		}
		if (!quote && *tmp != '\'' && *tmp != '\"')
			str_list->name[i++] = *tmp;
		quote = (!quote && *tmp == '\'') + (!quote && *tmp == '\"') * 2
			+ (quote == 1 && *tmp != '\'') + (quote == 2 && *tmp != '\"');
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
		if (quote != 1 && str[i] == '$')
		{
			str[i] = '\0';
			tmp = extract_env(shell, str + i + 1, quote);
			ret = ft_strjoin(str, tmp);
			free(tmp);
			if (ret == NULL)
				error_exit("malloc");
			return (ret);
		}
		quote = (!quote && str[i] == '\'') + (!quote && str[i] == '\"') * 2
			+ (quote == 1 && str[i] != '\'') + (quote == 2 && str[i] != '\"');
		++i;
	}
	ret = ft_strdup(str);
	if (ret == NULL)
		error_exit("malloc");
	return (ret);
}

char	*extract_env(t_shell *shell, char *str, int quote)
{
	char	*env_str;
	char	*tmp;
	char	*ret;
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\'' && str[i] != '\"')
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
