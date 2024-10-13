/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:49:00 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/13 18:20:44 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	count_token(char *str)
{
	int	word_flag;
	int	quote_flag;
	int	ret;

	word_flag = 0;
	quote_flag = 0;
	ret = 0;
	while (*str)
	{
		if ((quote_flag == 1 && *str == '\'')
			|| (quote_flag == 2 && *str == '\"'))
			quote_flag = 0;
		else if (!quote_flag)
		{
			quote_flag = (*str == '\'') + (*str == '\"') * 2;
			if (!word_flag && *str != ' ')
				++ret;
			word_flag = (*str != ' ');
		}
		++str;
	}
	return (ret);
}

char	*get_token(char *str)
{
	int		quote_flag;
	size_t	i;

	quote_flag = 0;
	i = 0;
	while (str[i])
	{
		if ((quote_flag == 1 && str[i] == '\'')
			|| (quote_flag == 2 && str[i] == '\"'))
			quote_flag = 0;
		else if (!quote_flag && str[i] == ' ')
			return (ft_substr(str, 0, i));
		else if (!quote_flag)
			quote_flag = (str[i] == '\'') + (str[i] == '\"') * 2;
		++i;
	}
	return (ft_substr(str, 0, i));
}

char	**lexer(char *input)
{
	char	**ret;
	int		i;

	ret = (char **)ft_calloc(sizeof(char *) * (count_token(input) + 1), 1);
	if (ret == NULL)
	{
		perror("ft_calloc error\n");
		exit(1);
	}
	i = 0;
	while (*input)
	{
		while (*input == ' ')
			++input;
		if (*input == '\0')
			break ;
		ret[i] = get_token(input);
		if (ret[i] == NULL)
		{
			perror("ft_substr error\n");
			exit(1);
		}
		input += ft_strlen(ret[i++]);
	}
	return (ret);
}
