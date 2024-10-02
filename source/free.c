/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:06:02 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/02 13:03:59 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command(t_command *command)
{
	t_command	*current;

	current = command;
	while (command != NULL)
	{
		current = command->next;
		free_arg(command->arg);
		free_inpath(command->inpath);
		free_outpath(command->outpath);
		free(command);
		command = current;
	}
}

void	free_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] != NULL)
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}

void	free_inpath(t_inpath *inpath)
{
	t_inpath *temp;

	while (inpath != NULL)
	{
		temp = inpath->next;
		free(inpath);
		inpath = temp;
	}
}

void	free_outpath(t_outpath *outpath)
{
	t_outpath *temp;

	while (outpath != NULL)
	{
		temp = outpath->next;
		free(outpath);
		outpath = temp;
	}
}