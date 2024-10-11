/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:51:06 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/11 16:34:24 by jose-lfe         ###   ########.fr       */
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
	dollar_checker(input, envp, data);
	return (false);
}

void	exit_statut(char **str, int i, t_data *data)
{
	*str = ft_change_str(*str, ft_itoa(data->exit_status), i, 2);
}
