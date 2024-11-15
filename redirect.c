/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:01:37 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/15 18:36:46 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	redirect_each(t_shell *shell, t_mlist *redirect)
{
	int	fd;

	printf("redirect: %s\n", redirect->next->name);
	if (redirect->name[1] == '<')
		return (here_doc(shell, redirect->next->name));
	else if (redirect->name[1] == '>')
		fd = open(redirect->next->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (redirect->name[0] == '<')
		fd = open(redirect->next->name, O_RDONLY | O_EXCL);
	else
		fd = open(redirect->next->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("mini: ", 2);
		perror(redirect->next->name);
		return (-1);
	}
	push_fd(shell, fd, NULL);
	if (dup2(fd, redirect->name[0] == '>') == -1)
		error_exit("dup2");
	return (0);
}

int	redirect_all(t_shell *shell, t_mlist *redirect)
{
	while (redirect)
	{
		if (redirect_each(shell, redirect) == -1)
			return (-1);
		redirect = redirect->next->next;
	}
	return (0);
}
