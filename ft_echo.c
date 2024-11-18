/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:26:19 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/18 14:28:40 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void    space_words_print(char **word, int newlineflag)
{
    int    i;

    i = 0;
    while (word[i] != NULL)
    {
        if (i == 0)
            printf("%s", word[i]);
        else
            printf(" %s", word[i]);
        i++;
    }
    if (newlineflag == 0)
        printf("\n");
}

int    has_option(char **commands)
{
    int    i;

    i = 1;
    if (commands[1][0] != '-')
        return (0);
    while (commands[1][i] != '\0')
    {
        if (commands[1][i] != 'n')
            return (0);
        i++;
    }
    return (1);
}

int    is_option(char *commands)
{
    int    i;

    i = 1;
    if (commands[0] != '-')
        return (1);
    while (commands[i] != '\0')
    {
        if (commands[i] != 'n')
            return (1);
        i++;
    }
    return (0);
}

int    ft_echo(char **command)
{
    int    newlineflag;
    int    i;

    newlineflag = 0;
    i = 1;
    if (command[1] == NULL)
    {
        printf("\n");
        return (0);
    }
    newlineflag = has_option(command);
    while (command[i] != NULL)
    {
        if (is_option(command[i]) == 1)
            break ;
        i++;
    }
    space_words_print(&command[i], newlineflag);
    return (0);
}