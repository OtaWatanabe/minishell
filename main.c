/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:44:22 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/21 20:31:29 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char	*input;
	char	**tokens;
	t_shell	shell;

	init_shell(&shell);
	(void)argc;
	(void)argv;
	(void)env;
	while (1)
	{
		input = get_input();
		tokens = lexer(input);
		free(input);
		shell.commands = parser(tokens);
		free_char_array(tokens);
		pipe_all(&shell);
		free_commands(shell.commands);
	}
}
