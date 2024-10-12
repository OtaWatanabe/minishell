/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 20:15:27 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/12 18:26:17 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

// int	main()
// {
// 	while (1)
// 	{
// 		char *str = get_input();
// 		printf("%s\n", str);
// 	}
// }

int	check_quote_status(char *str, int squote, int dquote)
{
	while (*str)
	{
		if (squote && *str == '\'')
			squote = 0;
		else if (dquote && *str == '\"')
			dquote = 0;
		else if (squote == 0 && dquote == 0 && *str == '\'')
			squote = 1;
		else if (squote == 0 && dquote == 0 && *str == '\"')
			dquote = 1;
		++str;
	}
	return (squote + dquote * 2);
}

char	*free_strjoin(char *str_1, char *str_2)
{
	char	*ret;
	size_t	i;
	size_t	j;
	
	ret = ft_calloc(ft_strlen(str_1) + ft_strlen(str_2) + 2, 1);
	if (ret == NULL)
	{
		perror("malloc error\n");
		exit(1);
	}
	i = 0;
	while (str_1[i])
	{
		ret[i] = str_1[i];
		++i;
	}
	ret[i++] = '\n';
	j = 0;
	while (str_2[j])
		ret[i++] = str_2[j++];
	free(str_1);
	free(str_2);
	return (ret);
}

char	*get_input(void)
{
	char	*line;
	char	*joined;
	int		quote_status;

	line = readline("minishell > ");
	quote_status = check_quote_status(line, 0, 0);
	joined = line;
	while (quote_status)
	{
		line = readline("> ");
		quote_status = check_quote_status(line, quote_status % 2, quote_status / 2);
		joined = free_strjoin(joined, line);
	}
	return (joined);
}
