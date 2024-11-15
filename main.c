/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:44:22 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/13 20:12:41 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char	*input;
	char	**tokens;
	t_shell	shell;

	init_shell(&shell, env);
	(void)argc;
	(void)argv;
	while (1)
	{
		input = get_input();
		if (input == NULL)
		{
			free_path(shell.env_path);
			return (0);
		}
		tokens = lexer(input);
		free(input);
		shell.commands = parser(&shell, tokens);
		free_char_array(tokens);
		pipe_all(&shell);
		free_commands(shell.commands);
	}
}
