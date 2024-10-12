/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:44:22 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/12 18:24:07 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char	*input;
	char	**tokens;
	t_tree	*tree;
	
	while (1)
	{
		input = get_input();
		tokens = lexer(input);
		free(input);
		tree = parser(tokens);
		free(tokens);
		minishell_execute(tree);
		free_tree(tree);
	}
}
