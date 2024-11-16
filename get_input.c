/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owatanab <owatanab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:15:27 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/16 18:19:25 by owatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*get_input(t_shell *shell)
{
	char	*line;

	shell->sa.sa_handler = read_handler;
	if (sigaction(SIGINT, &shell->sa, NULL) == -1)
        error_exit("sigaction");
	line = readline("minishell > ");
	if (line == NULL)
		return (NULL);
	while (*line == '\0')
	{
		free(line);
		line = readline("minishell > ");
		if (line == NULL)
			return (NULL);
	}
	add_history(line);
	return (line);
}
