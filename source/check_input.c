/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:51:06 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/25 12:03:26 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_input(char **input)
{
	if (check_quote(*input))
	{
		write(1, "Error: quotes are wrong\n", 24);
		return (true);
	}
	if (check_redir(*input))
	{
		write(1, "Syntax error near <>\n", 21);
		return (true);
	}
	return (false);
}

bool	is_all_space(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (true);
	while (str[i])
	{
		if (!is_white_space(str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	ft_accept(char c)
{
	if (c == '(' || c == ')')
		return (0);
	if (c == '[' || c == ']')
		return (0);
	if (c == '\0')
		return (0);
	else
		return (1);
}

bool	check_redir2(char *str, char c)
{
	int	i;

	i = 0;
	if (str[i + 1] && (str[i + 1]) == c)
		i++;
	if (str[i + 1])
		i++;
	if (str[i + 1] && is_redir(str[i]))
		return (true);
	if (str[i + 1])
		i++;
	while (is_white_space(str[i]) && str[i] != '\0')
		i++;
	if (str[i] == '|')
		return (true);
	if (ft_accept(str[i]) == 0)
		return (true);
	return (false);
}

bool	check_redir(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		while (is_white_space(str[i]))
			i++;
		if (str[i] == '<')
		{
			if (check_redir2(str + i, '<'))
				return (true);
		}
		if (str[i] == '>')
		{
			if (check_redir2(str + i, '>'))
				return (true);
		}
		while (!is_white_space(str[i]) && str[i] != '\0')
			i++;
	}
	return (false);
}
