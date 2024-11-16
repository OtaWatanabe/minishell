/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:26:47 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/16 09:36:36 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*join_3(char *str1, char *str2, char *str3)
{
	char	*tmp;
	char	*ret;

	tmp = ft_strjoin(str1, str2);
	if (tmp == NULL)
		error_exit("malloc");
	ret = ft_strjoin(tmp, str3);
	if (ret == NULL)
		error_exit("malloc");
	free(tmp);
	return (ret);
}

void	set_env_array(t_shell *shell, char *name, char *str)
{
	size_t	i;
	char	**tmp;

	i = 0;
	while (shell->env_array && shell->env_array[i])
	{
		if (ft_strncmp(shell->env_array[i], name, ft_strlen(name)) == 0
			&& shell->env_array[i][ft_strlen(name)] == '=')
		{
			free(shell->env_array[i]);
			shell->env_array[i] = join_3(name, "=", str);
			return ;
		}
		++i;
	}
	tmp = ft_calloc(sizeof(char *) * (i + 2), 1);
	if (tmp == NULL)
		error_exit("malloc");
	copy_str_array(shell->env_array, tmp);
	free_char_array(shell->env_array);
	shell->env_array = tmp;
	tmp[i] = join_3(name, "=", str);
}

void	set_env(t_shell *shell, char *name, char *str)
{
	set_env_array(shell, name, str);
	if (ft_strncmp(name, "PATH", 5) == 0)
		set_path(shell, str);
}

char	*get_env(t_shell *shell, char *name)
{
	char	**env;
	char	*ret;

	env = shell->env_array;
	if (ft_strncmp(name, "?", 2) == 0)
	{
		ret = ft_itoa(shell->exit_status);
		if (ret == NULL)
			error_exit("malloc");
		return (ret);
	}
	while (env && *env)
	{
		if ((ft_strncmp(name, *env, ft_strlen(name)) == 0)
			&& (*env)[ft_strlen(name)] == '=')
			return (error_strdup(ft_strchr(*env, '=') + 1));
		++env;
	}
	return (error_strdup(""));
}
