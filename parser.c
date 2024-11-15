/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:30:07 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/15 15:16:16 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	add_redirect(t_shell *shell, t_mlist **redirect, char **tokens)
{
	if (tokens[1] == NULL)
		return (syntax_error(shell, NULL));
	if (tokens[1][0] == '|' || tokens[1][0] == '<' || tokens[1][0] == '>')
		return (syntax_error(shell, tokens[1]));
	add_list(redirect, *tokens, NULL, 0);
	add_list(redirect, tokens[1], NULL, 0);
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
		if ((**tokens == '<' || **tokens == '>')
			&& add_redirect(shell, &commands->redirect, tokens++) == -1)
			return (-1);
		else if (**tokens != '<' && **tokens != '>')
			add_list(&commands->tmp, *tokens, NULL, 0);
		++tokens;
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
	return (ret);
}
