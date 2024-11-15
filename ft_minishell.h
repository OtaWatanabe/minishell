/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:44:52 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/15 18:06:21 by otawatanabe      ###   ########.fr       */
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
	int					command_len;
	int					exit_status;
	char				**command;
	t_mlist				*tmp;
	t_mlist				*redirect;
}	t_command;

typedef struct s_shell
{
	t_mlist		*open_fd;
	t_mlist		*pid;
	t_mlist		*tmpfile;
	char		**env_path;
	int			pipe_fd[2];
	t_mlist		*env_list;
	char		**env_array;
	t_command	*commands;
	int			out_fd_dup;
	int			in_fd_dup;
}	t_shell;

void		add_list(t_mlist **list, char *name, char *str, int num);
int			add_redirect(t_shell *shell, t_mlist **redirect, char **tokens);
int			ambiguous_error(t_shell *shell, char *str);
void		built_in(t_shell *shell, char **command);
void		clean_shell(t_shell *shell);
void		close_files(t_shell *shell);
void		command_error(char *command);
void		command_execute(t_shell *shell, t_command *command);
char		*command_path(t_shell *shell, char *command);
void		copy_str_array(char **from, char **to);
int			create_file(char *filename);
void		error_exit(char *str);
int			expand_all(t_shell *shell, t_command *commands);
char		*expand_env(t_shell *shell, char *str, int quote);
int			expand_list(t_shell *shell, t_mlist **list, int if_redirect);
t_mlist		*expand_split(t_mlist *str_list);
char		*extract_env(t_shell *shell, char *str, int quote);
void		free_char_array(char **array);
void		free_commands(t_command *commands);
void		free_entire_list(t_mlist *list);
void		free_list_element(t_mlist *list);
void		free_shell(t_shell *shell);
char		*get_env(t_shell *shell, char *name);
char		*get_input(void);
int 		get_quote_status(int quote, char c);
int			here_doc(t_shell *shell, char *eof);
char		*h_expand_env(t_shell *shell, char *str);
void		init_env_list(t_shell *shell, char **env);
void		init_shell(t_shell *shell, char **env);
char		**lexer(char *input);
char		**list_to_array(t_mlist *list);
int			mini_execute(t_shell *shell, t_command *commands, int fd);
t_command	*parser(t_shell *shell, char **tokens);
void		pipe_all(t_shell *shell);
void		push_fd(t_shell *shell, int fd, char *file);
int			redirect_all(t_shell *shell, t_mlist *redirect);
void		reset_fd(t_shell *shell);
void		set_env(t_shell *shell, char *name, char *str);
char		*set_next(t_mlist **str_list, char *str, int if_first);
void		set_path(t_shell *shell, char *str);
void		skip_null(t_mlist **list);
char		*skip_space(char *str);
void		split_env(t_mlist *env, char *str);
int			split_tokens(t_shell *shell, t_command *commands, char **tokens);
int			syntax_error(t_shell *shell, char *str);

#endif
