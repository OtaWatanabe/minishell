/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 13:17:27 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/12/01 13:19:22 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*free_strjoin(char *s1, char *s2)
{
	char	*ret;

	if (s1 == NULL || s2 == NULL)
		error_exit("malloc");
	ret = ft_strjoin(s1, s2);
	if (ret == NULL)
		error_exit("malloc");
	free(s1);
	free(s2);
	return (ret);
}

char	*error_strdup(char *str)
{
	char	*ret;

	if (str == NULL)
		return (NULL);
	ret = ft_strdup(str);
	if (ret == NULL)
		error_exit("malloc");
	return (ret);
}
