/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 18:01:37 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/18 10:25:04 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	redirect_each(t_shell *shell, t_command *commands, t_mlist *redirect)
{
	int	fd;

	if (redirect->str[1] == '<')
		fd = here_doc(shell, redirect);
	else if (redirect->str[1] == '>')
		fd = open(redirect->name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (redirect->str[0] == '<')
		fd = open(redirect->name, O_RDONLY | O_EXCL);
	else
		fd = open(redirect->name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (redirect->str[0] == '<')
		commands->in_fd = fd;
	else
		commands->out_fd = fd;
	if (fd == -1)
	{
		if (g_signal)
			return (-1);
		ft_putstr_fd("mini: ", 2);
		perror(redirect->name);
		return (-1);
	}
	return (0);
}

void	redirect_all(t_shell *shell)
{
	t_command	*commands;
	t_mlist		*redirect;

	shell->sa.sa_handler = heredoc_handler;
	if (sigaction(SIGINT, &shell->sa, NULL) == -1)
		error_exit("sigaction");
	commands = shell->commands;
	while (commands)
	{
		commands->out_fd = 1;
		redirect = commands->redirect;
		while (redirect)
		{
			if (redirect->name[0] == '<' && commands->in_fd != 0)
				close(commands->in_fd);
			else if (redirect->name[0] == '>' && commands->out_fd != 1)
				close(commands->out_fd);
			if (redirect_each(shell, commands, redirect) == -1)
				break ;
			redirect = redirect->next;
		}
		if (g_signal)
			return ;
		commands = commands->next;
	}
}
