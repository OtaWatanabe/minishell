/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otawatanabe <otawatanabe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:49:00 by otawatanabe       #+#    #+#             */
/*   Updated: 2024/10/21 20:32:36 by otawatanabe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int	check_special(char *str)
{
	if (*str == '<')
	{
		if (str[1] == '<' && str[2] && str[2] != ' ')
			return (1);
		if (str[1] != ' ' && str[1])
			return (1);
		return (0);
	}
	if (*str == '>')
	{
		if (str[1] == '>' && str[2] && str[2] != ' ')
			return (1);
		if (str[1] != ' ' && str[1])
			return (1);
		return (0);
	}
	if (*str == '|' && str[1] && str[1] != ' ')
		return (1);
	if (*str != ' ' && (str[1] == '<' || str[1] == '>' || str[1] == '|'))
		return (1);
	return (0);
}

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
		ret += check_special(str);
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
		if (ft_strncmp(str, "<<", 2) == 0 || ft_strncmp(str, ">>", 2) == 0)
			++str;
		++str;
	}
	return (ret);
}

char	*special_case(char *str)
{
	if (ft_strncmp(str, "<<", 2) == 0 || ft_strncmp(str, ">>", 2) == 0)
		return (ft_substr(str, 0, 2));
	return (ft_substr(str, 0, 1));
}

char	*get_token(char *str)
{
	int		quote_flag;
	size_t	i;

	quote_flag = 0;
	i = 0;
	if (*str == '<' || *str == '>' || *str == '|')
		return (special_case(str));
	while (str[i])
	{
		if ((quote_flag == 1 && str[i] == '\'')
			|| (quote_flag == 2 && str[i] == '\"'))
			quote_flag = 0;
		else if (!quote_flag && (str[i] == ' ' || str[i] == '<'
				|| str[i] == '>' || str[i] == '|'))
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
