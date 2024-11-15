/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:44:22 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/15 18:19:12 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	print_char_array(char **array)
{
	printf("print_char_array\n");
	while (*array)
	{
		printf("%s\n", *array);
		++array;
	}
}

void	print_commands(t_command *commands)
{
	while (commands)
	{
		t_mlist	*redirect = commands->redirect;

		printf("str_list\n");
		print_char_array(commands->command);
		printf("redirect\n");
		while (redirect)
		{
			printf("%s\n", redirect->name);
			redirect = redirect->next;
		}
		commands = commands->next;
	}
}

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
			free_shell(&shell);
			return (0);
		}
		tokens = lexer(input);
		free(input);
		shell.commands = parser(&shell, tokens);
		print_commands(shell.commands);
		free_char_array(tokens);
		pipe_all(&shell);
		free_commands(shell.commands);
	}
}
