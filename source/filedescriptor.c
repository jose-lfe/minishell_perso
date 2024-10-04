/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filedescriptor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:20:11 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/04 12:41:34 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_original_std(t_data *data, t_command *command)
{
	if (!command->pipein && data->base_stdin >= 0) {
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

void	ft_copy_original_std(t_data *data)
{
	data->base_stdin = dup(STDIN_FILENO);
	if (data->base_stdin == -1)
	{
		perror("dup STDIN");
		exit(EXIT_FAILURE);
    }
	data->base_stdout = dup(STDOUT_FILENO);
	if (data->base_stdout == -1)
	{
		perror("dup STDOUT");
		close(data->base_stdin);
		exit(EXIT_FAILURE);
	}
}

void	ft_redirect_fd(int i, int *fd)
{
	if (i == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (i == 1)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
}
