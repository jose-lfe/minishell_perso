/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:27:03 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/01 14:29:08 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_inredir(t_inpath *inpath)
{
	while (inpath)
	{
		if (inpath->here_doc == true)
		{
			ft_heredoc(inpath);
			inpath = inpath->next;
			continue ;
		}
		if (access(inpath->filename, F_OK) == -1)
		{
			perror(inpath->filename);
			perror(": no such file or directory\n");
			return (1);
		}
		if (access(inpath->filename, R_OK) == -1)
		{
			perror(inpath->filename);
			perror(": Permission denied\n");
			return (1);
		}
		ft_change_stdin(inpath);
		inpath = inpath->next;
	}
	return (0);
}

int	ft_outredir(t_outpath *outpath)
{
	int	fd;

	while (outpath)
	{
		if (access(outpath->filename, F_OK) != -1)
			if (access(outpath->filename, W_OK) == -1)
			{
				perror(outpath->filename);
				perror(": Permission denied\n");
				return (1);
			}
		if (outpath->append == false)
			fd = open(outpath->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(outpath->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		outpath =outpath->next;
	}
	return (0);
}

void	ft_heredoc(t_inpath *inpath)
{
    char    *input;
	char	*buffer;
	int		fd[2];

	buffer = NULL;
	if (pipe(fd) < 0)
	{
		perror("pipe error\n");
		return ;
	}
	while (1)
	{
		input = readline("readline> ");
		if (ft_strncmp(input, inpath->filename, ft_strlen(input)) != 0)
			break;
		buffer = ft_strjoin_gnl(buffer, input);
	}
	if (inpath->next == NULL)
		ft_putstr_fd(buffer, fd[1]);
	close(fd[1]);
	if (inpath->next == NULL)
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	free(buffer);
	free(input);
}

void	ft_change_stdin(t_inpath *inpath)
{
	int	fd;

	fd = open(inpath->filename, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}
