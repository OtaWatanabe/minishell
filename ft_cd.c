/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:26:14 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/11/18 15:43:53 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char	*exist_str(char **env, char *search, int len)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (env[count] != NULL)
		count++;
	while (i < count)
	{
		if (ft_strncmp(env[i], search, len) == 0)
			return (&env[i][len]);
		i++;
	}
	return (NULL);
}

int	pwd_set(t_shell *shell, int flag)
{
	char	*str;
	char	*env_str;

	str = getcwd(NULL, 0);
	if (str == NULL)
		error_exit("malloc");
	env_str = get_env(shell, "PWD");
	if (env_str == NULL)
	{
		free(str);
		error_exit("malloc");
	}
	if (flag == 2)
		set_env(shell, "OLDPWD", env_str);
	set_env(shell, "PWD", str);
	free(str);
	free(env_str);
	return (0);
}

int	chdir_set(t_shell *shell, char *path_str)
{
	if (chdir(path_str) != 0)
	{
		ft_putstr_fd("mini: cd:", 2);
		perror(path_str);
		return (1);
	}
	pwd_set(shell, 2);
	pwd_set(shell, 1);
	return (0);
}

int	ft_cd(t_shell *shell, char **command)
{
	char *cd_str;
	int ret;

	if (shell->if_pipe)
		return (0);
	if (command[1] == NULL || command[1][0] == '\0')
	{
		cd_str = get_env(shell, "HOME");
		ret = chdir_set(shell, cd_str);
		free(cd_str);
		return (ret);
	}
	if (chdir_set(shell, command[1]) != 0)
		return (1);
	else
		return (0);
}