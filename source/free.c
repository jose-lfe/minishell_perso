/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:06:02 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/09 14:44:57 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command(t_command *command)
{
	t_command	*current;

	if (command == NULL)
		return ;
	current = command;
	if (command->inpath)
		free_inpath(command->inpath);
	if (command->outpath)
		free_outpath(command->outpath);
	while (command != NULL)
	{
		current = command->next;
		free_arg(command->arg);
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

void	ft_free_data(t_data *data)
{
	if (data != NULL)
		free(data);
	return ;
}