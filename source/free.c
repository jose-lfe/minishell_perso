/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:06:02 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/04 13:43:50 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command(t_command *command)
{
	t_command	*current;

	current = command;
	while (command != NULL)
	{
		printf("free\n");
		current = command->next;
		printf("free2\n");
		free_arg(command->arg);
		printf("free3\n");
		if (command->inpath)
			free_inpath(command->inpath);
		printf("free4\n");
		if (command->outpath)
			free_outpath(command->outpath);
		printf("free5\n");
		free(command);
		printf("free6\n");
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
		if (inpath->filename)
			free(inpath->filename);
		if (inpath)
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
		if (outpath->filename)
			free(outpath->filename);
		if (outpath)
			free(outpath);
		outpath = temp;
	}
}