/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:44:52 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/14 11:26:38 by otawatanabe      ###   ########.fr       */
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

typedef struct s_command
{
	struct s_command	*next;
	int					command_len;
	int					exit_status;
	t_list				*str_list;
}	t_command;

typedef	struct s_list
{
	struct s_list	*next;
	int				num;
	char			*name;
	char			*str;
}	t_list;

typedef struct s_shell
{
	t_list		*open_fd;
	t_list		*pid;
	t_list		*tmpfile;
	char		**env_path;
	int			pipe_fd[2];
	t_list		*env;
	t_command	*commands;
	int			out_fd_dup;
	int			in_fd_dup;
}	t_shell;

int			add_list(t_list **list, char *name, char *str, int num);
void		clean_shell(t_shell *shell);
void		close_files(t_shell *shell);
void		command_error(char *command);
char		*command_path(t_shell *shell, char *command);
int			create_file(char *filename);
void		error_exit(char *str);
int			expand_all(t_shell *shell, t_command *commands);
int			expand_command(t_shell *shell, t_command *commands);
char		*expand_env(t_shell *shell, char *str, int quote);
t_list		*expand_split(t_list *str_list);
char		*extract_env(t_shell *shell, char *str, int quote);
void		free_char_array(char **array);
void		free_commands(t_command *tree);
void		free_entire_list(t_list *list);
void		free_list_element(t_list *list);
char		*get_env(t_shell *shell, char *name);
char		*get_input(void);
int			here_doc(t_shell *shell, char *eof);
void		init_env(t_shell *shell, char **env);
void		init_shell(t_shell *shell, char **env);
char		**lexer(char *input);
int			mini_execute(t_shell *shell, t_command *commands, int fd);
t_command	*parser(t_shell *shell, char **tokens);
void		pipe_all(t_shell *shell);
int			push_fd(t_shell *shell, int fd, char *file);
char		**remove_redirect(t_shell *shell, t_command *commands);
int			reset_fd(t_shell *shell);
int			set_env(t_shell *shell, char *name, char *str);
char		*set_next(t_list **str_list, char *str, int if_first);
void		set_path(t_shell *shell, char *str);
void		split_set(t_list *env, char *str);
void		split_tokens(t_shell *shell, t_command *commands, char **tokens);
void		syntax_error(char *str);

#endif
