/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:23:27 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/11/01 12:02:15 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern pid_t	g_glob_pid;

void	do_heredoc2(t_command *tmp, t_inpath *tmp_inpath, t_data *data)
{
	int	fd[2];
	
	pipe(fd);
	g_glob_pid = fork();
	if (g_glob_pid == 0)
		ft_heredoc(tmp_inpath, data, fd);
	waitpid(g_glob_pid, &data->exit_status, 0);
	ft_putstr_fd("apres waitpid heredoc\n", 2); //
	if (!tmp_inpath->next || tmp_inpath->index != tmp_inpath->next->index)
		tmp->fd_heredoc = fd[0];
	else
		close(fd[0]);
	close(fd[1]);
	if (WIFEXITED(data->exit_status))
		data->exit_status = WEXITSTATUS(data->exit_status);
	else if (WIFSIGNALED(data->exit_status))
		data->exit_status = 128 + WTERMSIG(data->exit_status);
	if (data->exit_status == 130)
	{
		ft_putstr_fd("exit status 130\n", 2);
	}
}

void	do_heredoc(t_command **command, t_data *data)
{
	t_command	*tmp;
	t_inpath	*tmp_inpath;
	int			i;

	i = 0;
	tmp = *command;
	while (tmp)
	{
		tmp_inpath = tmp->inpath;
		while (tmp && tmp_inpath)
		{
			if (tmp->inpath->heredoc == true && tmp->inpath->index == i)
			{
				do_heredoc2(tmp, tmp_inpath, data);
				// g_glob_pid = fork();
				// if (g_glob_pid == 0)
				// 	ft_heredoc(tmp, i, data);
				// waitpid(g_glob_pid, &data->exit_status, 0);
				// if (WIFEXITED(data->exit_status))
				// 	data->exit_status = WEXITSTATUS(data->exit_status);
				// else if (WIFSIGNALED(data->exit_status))
				// 	data->exit_status = 128 + WTERMSIG(data->exit_status);
				if (data->exit_status == 130)
					return ;
			}
			tmp_inpath = tmp_inpath->next;
		}
		i++;
		tmp = tmp->next;
	}
}

void	ft_heredoc(t_inpath *inpath, t_data *data, int *fd)
{
	char	*buffer;
	char	*lim;
	ssize_t	b_read;

	dup2(data->base_stdin, STDIN_FILENO);
	buffer = ft_calloc(1024, sizeof(char));
	lim = ft_strjoin(inpath->filename, "\n");
	b_read = ft_read_buffer(buffer, 0);
	while (ft_strncmp(buffer, lim, b_read) != 0)
	{
		if (!inpath->next || inpath->next->index != inpath->index)
			ft_putstr_fd(buffer, fd[1]);
		free(buffer);
		buffer = ft_calloc(1024, sizeof(char));
		b_read = ft_read_buffer(buffer, b_read);
	}
	free(buffer);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	free(lim);
	exit(0);
}
