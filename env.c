/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:26:47 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/15 15:14:25 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	set_env_list(t_shell *shell, char *name, char *str)
{
	t_mlist	*tmp;
	t_mlist	*new;

	tmp = shell->env_list;
	while (tmp && tmp->next && ft_strncmp(tmp->name, name, ft_strlen(name) + 1))
		tmp = tmp->next;
	if (tmp && ft_strncmp(tmp->name, name, ft_strlen(name) + 1) == 0)
	{
		free(tmp->str);
		tmp->str = ft_strdup(str);
		if (tmp->str == NULL)
			error_exit("malloc");
		return ;
	}
	new = (t_mlist *)ft_calloc(sizeof(t_mlist), 1);
	if (new == NULL)
		error_exit("malloc");
	new->name = ft_strdup(name);
	new->str = ft_strdup(str);
	if (new->name == NULL || new->str == NULL)
		error_exit("malloc");
	if (tmp == NULL)
		shell->env_list = new;
	else
		tmp->next = new;
}

void	set_env_array(t_shell *shell, char *name, char *str)
{
	size_t	i;
	char	**tmp;

	i = 0;
	while (shell->env_array[i])
	{
		if (ft_strncmp(shell->env_array[i], name, ft_strlen(name)) == 0
			&& shell->env_array[i][ft_strlen(name)] == '=')
		{
			free(shell->env_array[i]);
			shell->env_array[i] = ft_strjoin(name, ft_strjoin("=", str));
			if (shell->env_array[i] == NULL)
				error_exit("malloc");
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
	tmp[i] = ft_strjoin(name, ft_strjoin("=", str));
	if (tmp[i] == NULL)
		error_exit("malloc");
}

void	set_env(t_shell *shell, char *name, char *str)
{
	set_env_list(shell, name, str);
	set_env_array(shell, name, str);
	if (ft_strncmp(name, "PATH", 5) == 0)
		set_path(shell, str);
}

char	*get_env(t_shell *shell, char *name)
{
	t_mlist	*env;
	char	*ret;

	env = shell->env_list;
	while (env)
	{
		if (ft_strncmp(name, env->name, ft_strlen(env->name) + 1) == 0)
		{
			ret = ft_strdup(env->str);
			if (ret == NULL)
				error_exit("malloc");
			return (ret);
		}
		env = env->next;
	}
	ret = ft_strdup("");
	if (ret == NULL)
		error_exit("malloc");
	return (ret);
}
