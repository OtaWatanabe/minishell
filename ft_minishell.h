/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:44:52 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/13 18:22:00 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "libft/libft.h"

/*
t_sequenceは、コマンド、パイプ、セミコロンのいずれかを表す。
https://nafuka.hatenablog.com/entry/2021/03/29/194200
のブログの木構造を参考にした。
コマンドの時のみ、command変数を設定する。
そうでない時はNULLを入れる。
commandは、単語で区切った文字列の配列だが、リダイレクトなども含めて元の順番通り入れる。
例えば、
1.echo
2.hello
3.>
4.out
5.world!
のように分割して配列にするイメージ。
パスについては、コマンド実行時にcommand[0]から探す。
*/

typedef struct s_sequence
{
	struct s_sequemce	*next;
	char				*type;
	char				**command;
}	t_sequence;

void		execute(t_sequence *tree);
void		free_sequence(t_sequence *tree);
void		free_tokens(char **tokens);
char		*get_input(void);
char		**lexer(char *input);
t_sequence	*parser(char **tokens);

#endif
