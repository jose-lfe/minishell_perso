/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:06:02 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/24 14:16:22 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command(t_command *command)
{
	t_command	*next;
	int			in;
	int			out;

	in = 0;
	out = 0;
	if (command == NULL)
		return ;
	while (command != NULL)
	{
		if (in < 1)
			in = free_inpath(&(command->inpath));
		if (out < 1)
			out = free_outpath(&(command->outpath));
		command->outpath = NULL;
		next = command->next;
		if (command->arg)
			free_arg(command->arg);
		free(command);
		command = next;
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

int	free_inpath(t_inpath **inpath)
{
	t_inpath	*temp;

	if (!*inpath)
		return (0);
	while (*inpath != NULL)
	{
		temp = (*inpath)->next;
		if ((*inpath)->filename)
		{
			free((*inpath)->filename);
			(*inpath)->filename = NULL;
		}
		if (*inpath)
			free(*inpath);
		*inpath = NULL;
		*inpath = temp;
	}
	return (1);
}

int	free_outpath(t_outpath **outpath)
{
	t_outpath	*temp;

	if (!*outpath)
		return (0);
	while (*outpath != NULL)
	{
		temp = (*outpath)->next;
		if ((*outpath)->filename)
		{
			free((*outpath)->filename);
			(*outpath)->filename = NULL;
		}
		if (*outpath)
			free(*outpath);
		(*outpath) = temp;
	}
	*outpath = NULL;
	return (1);
}

void	ft_free_data(t_data *data)
{
	if (data != NULL)
		free(data);
	return ;
}
