/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:32:32 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/22 11:36:47 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern pid_t	g_glob_pid;

int	exec_pipe2(t_data *data, t_command *current, t_envp **envp, t_pipe p)
{
	int	error;

	while (current != NULL)
	{
		error = 0;
		if (current->next != NULL)
			pipe(p.fd);
		if (current->inpath && ft_inredir(current->inpath, p.i, data) == 1)
			error = 1;
		g_glob_pid = fork();
		if (g_glob_pid == 0 && error == 0)
			do_child(data, current, envp, p);
		else
			do_parent(current, &p);
		current = current->next;
		p.i++;
	}
	return (p.i);
}