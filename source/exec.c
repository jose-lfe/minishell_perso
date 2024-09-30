/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:38:47 by joseluis          #+#    #+#             */
/*   Updated: 2024/09/30 15:55:10 by jose-lfe         ###   ########.fr       */
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

	tmp = *command;
	while (tmp)
	{
		if (tmp->out_redir == true && ft_outredir(tmp->out_path) == 1)
		{
			tmp =tmp->next;
			continue ;
		}
		if (tmp->in_redir == true && ft_inredir(tmp->in_path) == 1)
		{
			tmp =tmp->next;
			continue ;
		}
		if (ft_exec_our_command(tmp, envp) == 0)
		{
			tmp =tmp->next;
			continue ;
		}
		if (!tmp->out_redir && (tmp->pipein || tmp->pipeout))
		{
			if (pipe(fd) < 0)
				perror("pipe error");
			tmp = tmp->next;
			continue ;
		}
	}
	ft_free_command(command);
}

int	ft_exec_our_command(t_command *command, t_envp **envp)
{
	int	i;

	i = ft_check_command(command, envp);
	if (i == -1)
		return (1);
	if (command->next)
	{
		
	}
}

int	ft_check_command(t_command *command, t_envp **envp)
{
	if (ft_strncmp(command->arg[1], "echo", ft_strlen(command->arg[1])) == 0)
		return (1);
	if (ft_strncmp(command->arg[1], "cd", ft_strlen(command->arg[1])) == 0)
		return (2);
	if (ft_strncmp(command->arg[1], "pwd", ft_strlen(command->arg[1])) == 0)
		return (3);
	if (ft_strncmp(command->arg[1], "export", ft_strlen(command->arg[1])) == 0)
		return (4);
	if (ft_strncmp(command->arg[1], "unset", ft_strlen(command->arg[1])) == 0)
		return (5);
	if (ft_strncmp(command->arg[1], "env", ft_strlen(command->arg[1])) == 0)
		return (6);
	if (ft_strncmp(command->arg[1], "exit", ft_strlen(command->arg[1])) == 0)
		return (7);
	if (ft_check_base_command(command, envp) == 0)
		return (8);
	if (ft_check_relative_path(command) == 0)
		return (9);
	return (-1);
}

int	check_base_command(t_command *command, t_envp **envp)
{
	t_envp	*tmp;
	char	**path;
	int		i;
	char	*cmd;

	tmp = *envp;
	while(tmp && ft_strncmp(tmp->var, "PATH", 4) != 0)
		tmp = tmp->next;
	if (!tmp)
		return (1);
	path = ft_split(tmp->value, ":");
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin_gnl(path[i], "/");
		i++;
	}
	// continuer
}

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

void	ft_change_stdin(t_inpath *inpath)
{
	int	fd;

	fd = open(inpath->filename, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
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
