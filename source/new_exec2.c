/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:32:32 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/11/01 11:46:11 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern pid_t	g_glob_pid;

pid_t	exec_pipe2(t_data *data, t_command *curr, t_envp **envp, t_pipe *p)
{
	int	error;

	error = 0;
	data->flag = 0;
	if (curr->next != NULL)
		pipe(p->fd);
	if (curr->inpath && ft_inredir(curr->inpath, p->i, data, curr) == 1)
		error = 1;
	g_glob_pid = fork();
	if (g_glob_pid == 0 && error == 0)
		do_child(data, curr, envp, *p);
	else
		do_parent(curr, p);
	curr = curr->next;
	return (g_glob_pid);
}

/*
int	exec_pipe2(t_data *data, t_command *current, t_envp **envp, t_pipe p)
{
	int	error;

	while (current != NULL)
	{
		error = 0;
		data->flag = 0;
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
}*/

int	ft_read_buffer(char *buffer, ssize_t b_read)
{
	ft_putstr_fd("heredoc> ", STDERR_FILENO);
	b_read = read(STDIN_FILENO, buffer, (1023));
	return (b_read);
}

void	exit_statut(char **str, int i, t_data *data)
{
	char	*tmp;

	tmp = ft_itoa(data->exit_status);
	*str = ft_change_str(*str, tmp, i, 1);
	free (tmp);
}
