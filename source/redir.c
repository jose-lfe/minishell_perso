/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:27:03 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/24 14:01:36 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_inredir(t_inpath *inpath, int i, t_data *data)
{
	while (inpath)
	{
		if (inpath->index == i && inpath->heredoc == true)
		{
			ft_heredoc(inpath, i, data);
			inpath = inpath->next;
			continue ;
		}
		if (inpath->index == i && access(inpath->filename, F_OK) == -1)
		{
			ft_putstr_fd(inpath->filename, 2);
			ft_putstr_fd(": no such file or directory\n", 2);
			return (1);
		}
		if (inpath->index == i && access(inpath->filename, R_OK) == -1)
		{
			ft_putstr_fd(inpath->filename, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			return (1);
		}
		if (inpath->index == i)
			ft_change_stdin(inpath, data);
		inpath = inpath->next;
	}
	return (0);
}

int	ft_outredir(t_outpath *outpath, int i)
{
	while (outpath)
	{
		if (outpath->index == i && access(outpath->filename, F_OK) != -1)
		{
			if (access(outpath->filename, W_OK) == -1)
			{
				ft_putstr_fd(outpath->filename, 2);
				ft_putstr_fd(": Permission denied\n", 2);
				return (1);
			}
		}
		if (outpath->index == i)
		{
			if (ft_outredir2(outpath) == 1)
				return (1);
		}
		outpath = outpath->next;
	}
	return (0);
}

int	ft_outredir2(t_outpath *outpath)
{
	int	fd;

	if (outpath->append == false)
		fd = open(outpath->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(outpath->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

void	ft_heredoc(t_inpath *inpath, int i, t_data *data)
{
	char	*buffer;
	int		fd[2];
	char	*lim;
	ssize_t	b_read;

	pipe(fd);
	dup2(data->base_stdin, STDIN_FILENO);
	buffer = ft_calloc(1024, sizeof(char));
	lim = ft_strjoin(inpath->filename, "\n");
	b_read = ft_read_buffer(buffer, 0);
	while (ft_strncmp(buffer, lim, b_read) != 0)
	{
		if (!inpath->next || inpath->next->index != i)
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
	data->flag = 1;
}

// void	ft_heredoc(t_inpath *inpath, int i, t_data *data)
// {
// 	char	*input;
// 	char	*buffer;
// 	int		fd[2];

// 	dup2(data->base_stdin, STDIN_FILENO);
// 	buffer = ft_strdup("");
// 	if (pipe(fd) < 0)
// 		return ;
// 	while (1)
// 	{
// 		input = readline("heredoc> ");
// 		if (ft_strncmp(input, inpath->filename, ft_strlen(input)) == 0 
// 		&& ft_strlen(input) > 0)
// 			break ;
// 		buffer = ft_strjoin(ft_strjoin_gnl(buffer, input), "\n");
// 		//free(buffer);
// 		//free(input);
// 	}
// 	if (!inpath->next || inpath->next->index != i)
// 		ft_putstr_fd(buffer, fd[1]);
// 	close(fd[1]);
// 	if (inpath->next == NULL || inpath->next->index != i)
// 		dup2(fd[0], STDIN_FILENO);
// 	close(fd[0]);
// 	free(input);
// }

void	ft_change_stdin(t_inpath *inpath, t_data *data)
{
	int	fd;

	fd = open(inpath->filename, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	data->flag = 1;
}
