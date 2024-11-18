/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:27:52 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/18 15:16:27 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int    ft_env(t_shell *shell)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (shell->env_array[count] != NULL)
        count++;
    while (i < count)
    {
        if (shell->env_array[i][0] != '\0')
            printf("%s\n", shell->env_array[i]);
        i++;
    }
    return (0);
}
