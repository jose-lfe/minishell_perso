/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:38:18 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/29 12:38:19 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_pipe2(char *str, char c)
{
	int	i;

	i = 0;
	if (str[i + 1] && (str[i + 1]) == c)
		return (true);
	if (str[i + 1])
		i++;
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
