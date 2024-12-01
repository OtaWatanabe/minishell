/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:30:07 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/12/01 14:23:24 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	add_redirect(t_shell *shell, t_command *command, char **tokens)
{
	if (tokens[1] == NULL)
		return (syntax_error(shell, "newline"));
	if (tokens[1][0] == '|' || tokens[1][0] == '<' || tokens[1][0] == '>')
		return (syntax_error(shell, tokens[1]));
	add_list(&command->redirect, tokens[1], tokens[0], 0);
	return (0);
}

int	split_tokens(t_shell *shell, t_command *commands, char **tokens)
{
	while (*tokens)
	{
		if (ft_strncmp(*tokens, "|", 2) == 0)
		{
			if (commands->tmp == NULL && commands->redirect == NULL)
				return (syntax_error(shell, "|"));
			commands->next = (t_command *)ft_calloc(sizeof(t_command), 1);
			if (commands->next == NULL)
				error_exit("malloc");
			return (split_tokens(shell, commands->next, tokens + 1));
		}
		if (**tokens == '<' || **tokens == '>')
		{
			if (add_redirect(shell, commands, tokens++) == -1)
				return (-1);
		}
		else
			add_list(&commands->tmp, *tokens, NULL, 0);
		++tokens;
	}
	return (0);
}

int	expand_all(t_shell *shell, t_command *commands)
{
	t_command	*tmp;

	tmp = commands;
	while (tmp)
	{
		expand_list(shell, &tmp->tmp);
		tmp->command = list_to_array(tmp->tmp);
		free_entire_list(tmp->tmp);
		tmp->tmp = NULL;
		if (expand_list(shell, &tmp->redirect) == -1)
			return (-1);
		tmp = tmp->next;
	}
	return (0);
}

t_command	*parser(t_shell *shell, char **tokens)
{
	t_command	*ret;

	if (*tokens == NULL)
		return (NULL);
	ret = (t_command *)ft_calloc(sizeof(t_command), 1);
	if (ret == NULL)
		error_exit("malloc");
	if (split_tokens(shell, ret, tokens) == -1 || expand_all(shell, ret) == -1)
	{
		free_commands(ret);
		return (NULL);
	}
	shell->if_pipe = 0;
	if (ret->next)
		shell->if_pipe = 1;
	return (ret);
}
