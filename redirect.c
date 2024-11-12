/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:01:37 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/12 10:47:19 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	redirect(t_shell *shell, char **redirect)
{
	int	fd;

	if (redirect[0][1] == '<')
		return (here_doc(shell, redirect[1]));
	else if (redirect[0][1] == '>')
		fd = open(redirect[1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (redirect[0][0] == '<')
		fd = open(redirect[1], O_RDONLY | O_EXCL);
	else
		fd = open(redirect[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("mini: ", 2);
		perror(redirect[1]);
		return (-1);
	}
	if (push_fd(shell, fd, NULL) == -1)
		return (-1);
	if (dup2(fd, redirect[0][0] == '>') == -1)
	{
		perror("dup2");
		return (-1);
	}
	return (0);
}

int	check_strdup(char **ret, size_t i, char *str)
{
	ret[i] = ft_strdup(str);
	if (ret[i] == NULL)
	{
		perror("malloc");
		return (-1);
	}
	return (0);
}

char	**remove_redirect(t_shell *shell, t_command *commands)
{
	char	**ret;
	char	**command;
	size_t	i;

	i = 0;
	command = commands->command;
	ret = (char **)ft_calloc(commands->command_len + 1, 1);
	if (ret == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	while (*command)
	{
		if (((**command == '<' || **command == '>')
				&& redirect(shell, command) == -1)
			|| (**command != '<' && **command != '>'
				&& check_strdup(ret, i++, *command) == -1))
		{
			free_char_array(ret);
			return (NULL);
		}
		command += 1 + (command[0][0] == '<' || command[0][0] == '>');
	}
	return (ret);
}
