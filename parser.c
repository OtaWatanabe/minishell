/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:30:07 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/14 10:59:16 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	split_tokens(t_shell *shell, t_command *commands, char **tokens)
{
	t_list	*str_list;

	while (*tokens)
	{
		if (ft_strncmp(*tokens, "|", 2) == 0)
		{
			commands->next = (t_command *)ft_calloc(sizeof(t_command), 1);
			if (commands->next == NULL)
				error_exit("malloc");
			split_tokens(shell, commands->next, tokens + 1);
			return ;
		}
		if (**tokens == '<' || **tokens == '>')
			add_list(commands->str_list, *tokens, NULL, 1);
		else
			add_list(commands->str_list, *tokens, NULL, 0);
		++tokens;
	}
}

t_command	*parser(t_shell *shell, char **tokens)
{
	t_command	*ret;

	ret = (t_command *)ft_calloc(sizeof(t_command), 1);
	if (ret == NULL)
		error_exit("malloc");
	split_tokens(shell, ret, tokens);
	expand_all(shell, ret);
}
