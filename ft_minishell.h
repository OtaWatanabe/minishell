/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:44:52 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/12 18:24:45 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL
# define FT_MINISHELL

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "libft/libft.h"

/*
t_treeは、コマンド、パイプ、セミコロンのいずれかを表す。
https://nafuka.hatenablog.com/entry/2021/03/29/194200
のブログの木構造を参考にした。
コマンドの時のみ、command, redirectの変数を設定する。
パスについては、コマンド実行時にcommand[0]から探す。
*/

typedef struct s_tree
{
	struct s_tree	*left_child;
	struct t_tree	*right_child;
	char			*type;
	char			**command;
	char			**redirect_from;
	char			**redirect_to;
}	t_tree;

void	execute(t_tree *tree);
void	free_tree(t_tree *tree);
char	*get_input(void);
char	**lexer(char *input);
t_tree	*parser(char **tokens);

#endif
