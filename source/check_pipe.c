/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:38:18 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/11/01 14:14:30 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_accept2(char c)
{
	if (c == '(' || c == ')')
		return (0);
	if (c == '[' || c == ']')
		return (0);
	if (c == ' ')
		return (0);
	if (c == '\0')
		return (0);
	else
		return (1);
}

bool	check_pipe2(char *str, char c)
{
	int	i;

	i = 0;
	if (str[i + 1] && (str[i + 1]) == c)
		return (true);
	if (str[i + 1])
		i++;
	while (is_white_space(str[i]) && str[i] != '\0')
		i++;
	if (ft_accept2(str[i]) == 0 || str[i] == c)
		return (true);
	return (false);
}

bool	check_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		while (is_white_space(str[i]))
			i++;
		if (str[i] == '|')
		{
			if (check_pipe2(str + i, '|'))
				return (true);
		}
		while (!is_white_space(str[i]) && str[i] != '\0')
			i++;
	}
	return (false);
}
