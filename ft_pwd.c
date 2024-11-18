/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:28:04 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/18 14:28:04 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

/*
        getcwd(NULL,0)を指定すると現在のディレクトリの位置がmallocで確保されたchar配列が返る。
        そいつをprintfすればいい。
    */

int    ft_pwd(void)
{
    char    *buf;

    buf = getcwd(NULL, 0);
    if (buf == NULL)
    {
        perror("pwd:");
        return (1);
    }
    else
    {
        printf("%s\n", buf);
        free(buf);
    }
    return (0);
}