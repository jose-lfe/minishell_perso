/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:51:06 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/17 12:03:19 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_input(char **input, t_envp **envp, t_data *data)
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
	dollar_checker(input, envp, data);
	return (false);
}

void	exit_statut(char **str, int i, t_data *data)
{
	*str = ft_change_str(*str, ft_itoa(data->exit_status), i, 2);
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

bool	check_redir(char *str)
{
	int	c_r;
	int	c_l;
	int	i;

	c_r = 0;
	c_l = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (check_redir2(str, &c_l, &c_r, &i) == true)
			return (true);
		if (i > 0)
		{
			if (str[i] == '>')
				c_r = 1;
		}
		i++;
	}
	return (false);
}

bool	check_redir2(char *str, int *c_l, int *c_r, int *i)
{
	if (*c_r == 1 && str[*i] == '<')
		return (true);
	if (*c_l == 1 && str[*i] == '>')
		return (true);
	while (str[*i] == '<' && str[*i] != '\0')
	{
		(*c_l)++;
		if (*c_l > 2)
			return (true);
		(*i)++;
	}
	while (str[*i] == '>' && str[*i] != '\0')
	{
		(*c_r)++;
		if (*c_r > 2)
			return (true);
		(*i)++;
	}
	if (*i > 0)
	{
		if (str[*i - 1] == '<')
			*c_l = 1;
	}
	return (false);
}
