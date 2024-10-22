/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:51:06 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/22 10:32:54 by jose-lfe         ###   ########.fr       */
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

void	exit_statut(char **str, int i, t_data *data)
{
	*str = ft_change_str(*str, ft_itoa(data->exit_status), i, 1);
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
	if (ft_isalpha(str[i]) == 0)
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
