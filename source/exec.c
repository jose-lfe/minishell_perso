/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:38:47 by joseluis          #+#    #+#             */
/*   Updated: 2024/09/26 17:00:37 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
commencer par verifier qu'il s'agit pas d'une des 7 commandes faite
s'occuper des pipes et redirection 
fork // regarder pipex 
execve
*/

void	start_exec(t_command **command, t_envp **envp)
{
	t_command	*tmp;
	int			fd[2];
	pid_t		pid;

	tmp = *command;
	while (tmp)
	{
		if (ft_outredir(tmp->out_path) == 1) // peut etre plutot verifier avant bool in_redir
			break ;
		if (ft_inredir(tmp->in_path) == 1)
			break ;
		if (tmp->pipein == true || tmp->pipeout == true)
		{
			tmp = tmp->next;
			continue ;
		}
	}
	ft_free_command(command);
}

int	ft_inredir(t_inpath *inpath)
{
	int	fd;

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
		} // a terminer
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

// signe << 
void	ft_heredoc(t_inpath *inpath)
{
    char    *input;
	char	*buffer;
	int		fd[2];

	buffer = NULL;
	if (pipe(fd) < 0)
	{
		perror("error de pipe\n");
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
