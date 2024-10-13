/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:44:22 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/13 18:22:20 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char		*input;
	char		**tokens;
	t_sequence	*seq;

	(void)argc;
	(void)argv;
	while (1)
	{
		input = get_input();
		tokens = lexer(input);
		free(input);
		seq = parser(tokens);
		free_tokens(tokens);
		minishell_execute(seq, env);
		free_sequence(seq);
	}
}
