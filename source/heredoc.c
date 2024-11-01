/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:23:27 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/11/01 13:40:41 by jose-lfe         ###   ########.fr       */
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
	if (!tmp_inpath->next || tmp_inpath->index != tmp_inpath->next->index)
		tmp->fd_heredoc = fd[0];
	else
		close(fd[0]);
	close(fd[1]);
	if (WIFEXITED(data->exit_status))
		data->exit_status = WEXITSTATUS(data->exit_status);
	else if (WIFSIGNALED(data->exit_status))
		data->exit_status = 128 + WTERMSIG(data->exit_status);
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
			if (tmp_inpath->heredoc == true && tmp_inpath->index == i)
			{
				do_heredoc2(tmp, tmp_inpath, data);
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
	struct sigaction	sa_int;
	char				*buffer;
	char				*lim;
	ssize_t				b_read;

	sa_int.sa_handler = SIG_DFL;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
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
	close(fd[1]);
	close(fd[0]);
	free(lim);
	exit(0);
}
