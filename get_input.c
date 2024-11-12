/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:15:27 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/10 22:58:08 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*get_input(void)
{
	char	*line;

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
