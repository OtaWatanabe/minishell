/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:56:57 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/13 18:23:08 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		++i;
	}
	free(tokens);
}

void	free_sequence(t_sequence *seq)
{
	t_sequence	*tmp;

	while (seq)
	{
		tmp = seq->next;
		free(seq->type);
		free(seq->command);
		free(seq);
		seq = tmp;
	}
}
