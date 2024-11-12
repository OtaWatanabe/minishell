/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:01:37 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/21 20:32:57 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	push_file(t_shell *shell, int fd, char *file)
{
	t_fd	*new;
	t_fd	*tmp;

	new = (t_fd *)ft_calloc(sizeof(t_fd), 1);
	if (new == NULL)
	{
		perror("malloc error\n");
		close(fd);
		if (file)
			unlink(file);
		return (-1);
	}
	new->fd = fd;
	new->file = file;
	if (shell->openfile == NULL)
	{
		shell->openfile = new;
		return (0);
	}
	tmp = shell->openfile;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}

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
		perror("bash: ");
		perror(redirect[1]);
		perror(strerror(errno));
		return (-1);
	}
	if (push_file(shell, fd, NULL) == -1)
		return (-1);
	if (dup2(fd, redirect[0][0] == '>') == -1)
	{
		perror("dup2 error\n");
		return (-1);
	}
	return (0);
}

int	check_strdup(char **ret, int i, char *str)
{
	ret[i] = ft_strdup(str);
	if (ret[i] == NULL)
	{
		perror("ft_strdup error\n");
		return (-1);
	}
	return (0);
}

char	**extract_redirect(t_shell *shell, t_command *commands)
{
	char	**ret;
	char	**command;
	int		i;

	i = 0;
	command = commands->command;
	ret = (char **)ft_calloc(commands->command_len + 1, 1);
	if (ret == NULL)
	{
		perror("ft_calloc error\n");
		return (NULL);
	}
	while (*command)
	{
		if (((command[0][0] == '<' || command[0][0] == '>')
			&& redirect(shell, command) == -1)
			|| (command[0][0] != '<' && command[0][0] != '>'
			&& check_strdup(ret, i++, *command) == -1))
		{
			free_char_array(ret);
			return (NULL);
		}
		command += 1 + (command[0][0] == '<' || command[0][0] == '>');
	}
	return (ret);
}
