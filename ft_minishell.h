/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:44:52 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/21 20:34:28 by otawatanabe      ###   ########.fr       */
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

/*
t_commandは、コマンドを表す。
commandは、単語で区切った文字列の配列だが、リダイレクトなども含めて元の順番通り入れる。
例えば、
1.echo
2.hello
3.>
4.out
5.world!
のように分割して配列にするイメージ。
コマンドの次は、必ずパイプかセミコロンが来て、その後にまだ処理が続く場合は必ずコマンドが来る。
なので、この構造体において、if_lastが1の時以外はパイプが続く。
このパターンに合わないような入力の場合、parser内でエラー処理をしてもらうことになる。
（例えば、パイプが2つ連続しているような場合）
また、リストの最後は、変数nextがNULLとなる。
command_lenは変数commandの文字列の数を表す。
パスについては、コマンド実行時にcommand[0]から探す。
*/

typedef struct s_command
{
	struct s_command	*next;
	int					if_last;
	int					command_len;
	int					exit_status;
	char				**command;
}	t_command;

typedef struct s_fd
{
	struct s_fd	*next;
	int			fd;
	char		*file;
}	t_fd;

typedef struct s_path
{
	struct s_path	*next;
	char			*path;
}	t_path;

typedef struct s_shell
{
	t_fd		*openfile;
	t_path		*env_path;
	int			pipe_fd[2];
	char		**env;
	char		*path;
	t_command	*commands;
	int			out_fd_dup;
	int			in_fd_dup;
}	t_shell;

void		close_files(t_shell *shell);
void		command_error(char *command);
char		*command_path(t_shell *shell, char *command);
int			create_file(char *filename);
void		existence_error(char *path);
char		**extract_redirect(t_shell *shell, t_command *commands);
void		free_sequence(t_command *tree);
void		free_char_array(char **array);
int			here_doc(t_shell *shell, char *eof);
int			mini_execute(t_shell *shell, t_command *commands, int fd);
char		*get_input(void);
char		**lexer(char *input);
t_command	*parser(char **tokens);
void		pipe_all(t_shell *shell);
int			push_file(t_shell *shell, int fd, char *file);
void		reset_fd(t_shell *shell);

#endif
