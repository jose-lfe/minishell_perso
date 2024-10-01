/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedescriptor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:20:11 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/01 14:20:33 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_original_std(t_data *data, t_command *command)
{
	if (!command->pipeout && data->base_stdin >= 0) {
		if (dup2(data->base_stdin, STDIN_FILENO) == -1)
		{
			perror("dup2 STDIN");
		}
    }
    if (data->base_stdout >= 0)
	{
		if (dup2(data->base_stdout, STDOUT_FILENO) == -1)
		{
			perror("dup2 STDOUT");
		}
	}
}
