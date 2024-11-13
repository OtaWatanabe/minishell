/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:44:52 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/13 11:03:11 by otawatanabe      ###   ########.fr       */
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
	char				**command;
}	t_command;

typedef struct s_env
{
	struct s_env	*next;
	char			*name;
	char			*str;
}	t_env;

typedef struct s_intlist
{
	struct s_fd	*next;
	int			num;
}	t_intlist;

typedef struct s_strlist
{
	struct s_strlist	*next;
	char				*str;
}	t_strlist;

typedef struct s_shell
{
	t_intlist	*open_fd;
	t_intlist	*pid;
	t_strlist	*tmpfile;
	char		**env_path;
	int			pipe_fd[2];
	t_env		*env;
	t_command	*commands;
	int			out_fd_dup;
	int			in_fd_dup;
}	t_shell;

void		add_intlist(t_strlist **list, int n);
int			add_strlist(t_strlist **list, char *str);
void		clean_shell(t_shell *shell);
void		close_files(t_shell *shell);
void		command_error(char *command);
char		*command_path(t_shell *shell, char *command);
int			create_file(char *filename);
void		free_char_array(char **array);
void		free_commands(t_command *tree);
void		free_path(t_strlist *path);
char		*get_input(void);
int			here_doc(t_shell *shell, char *eof);
void		init_env(t_shell *shell, char **env);
void		init_shell(t_shell *shell, char **env);
char		**lexer(char *input);
int			mini_execute(t_shell *shell, t_command *commands, int fd);
t_command	*parser(char **tokens);
void		pipe_all(t_shell *shell);
int			push_fd(t_shell *shell, int fd, char *file);
char		**remove_redirect(t_shell *shell, t_command *commands);
int			reset_fd(t_shell *shell);
int			set_env(t_shell *shell, char *name, char *str);
void		set_path(t_shell *shell, char *str);
void		split_set(t_env *env, char *str);

#endif
