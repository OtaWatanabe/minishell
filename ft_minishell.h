/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: owatanab <owatanab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:44:52 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/16 18:30:14 by owatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <signal.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>

extern int g_signal;

typedef struct s_mlist
{
	struct s_mlist	*next;
	int				num;
	char			*name;
	char			*str;
}	t_mlist;

typedef struct s_command
{
	struct s_command	*next;
	char				**command;
	t_mlist				*tmp;
	t_mlist				*redirect;
	int					in_fd;
	int					out_fd;
}	t_command;

typedef struct s_shell
{
	t_mlist				*open_fd;
	t_mlist				*pid;
	t_mlist				*tmpfile;
	char				**env_path;
	int					pipe_fd[2];
	char				**env_array;
	t_command			*commands;
	int					out_fd_dup;
	int					in_fd_dup;
	int					exit_status;
	int					if_pipe;
	struct sigaction	sa;
}	t_shell;

void		add_list(t_mlist **list, char *name, char *str, int num);
int			add_redirect(t_shell *shell, t_command *command, char **tokens);
int			ambiguous_error(t_shell *shell, char *str);
int			built_in(t_shell *shell, char **command);
void		clean_shell(t_shell *shell);
void		close_files(t_shell *shell);
void		command_error(char *command);
void		command_execute(t_shell *shell, t_command *command);
char		*command_path(t_shell *shell, char *command);
void		copy_str_array(char **from, char **to);
void		delete_files(t_shell *shell);
void		error_exit(char *str);
char		*error_strdup(char *str);
int			expand_all(t_shell *shell, t_command *commands);
char		*expand_env(t_shell *shell, char *str, int quote);
t_mlist		*expand_split(t_mlist *str_list);
char		*extract_env(t_shell *shell, char *str, int quote);
void		free_char_array(char **array);
void		free_commands(t_command *commands);
void		free_entire_list(t_mlist *list);
void		free_list_element(t_mlist *list);
void		free_shell(t_shell *shell);
char		*get_env(t_shell *shell, char *name);
char		*get_input(t_shell *shell);
int 		get_quote_status(int quote, char c);
int			here_doc(t_shell *shell, t_mlist *here);
void    	heredoc_handler(int signum);
char		*h_expand_env(t_shell *shell, char *str);
void		init_shell(t_shell *shell, char **env);
char		**lexer(char *input);
void    	init_sigaction(t_shell *shell);
char		**list_to_array(t_mlist *list);
void    	parent(int signum);
t_command	*parser(t_shell *shell, char **tokens);
void		pipe_all(t_shell *shell);
void    	read_handler(int signum);
void		redirect_all(t_shell *shell);
void		set_env(t_shell *shell, char *name, char *str);
char		*set_next(t_mlist **str_list, char *str, int if_first);
void		set_path(t_shell *shell, char *str);
void		skip_null(t_mlist **list);
char		*skip_space(char *str);
void		split_env(t_mlist *env, char *str);
int			split_tokens(t_shell *shell, t_command *commands, char **tokens);
int			syntax_error(t_shell *shell, char *str);

#endif
