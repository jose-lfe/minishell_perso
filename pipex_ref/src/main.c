/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:39:43 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/04/25 15:32:36 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

	// while (access(cmd_path, X_OK) != 0)
	// {
	// 	free(cmd_path);
	// 	cmd_path = ft_strjoin(info->path[++j], command[0]);
	// }
	// execve(cmd_path, command, info->env);
	// perror("execve");
	// free(cmd_path);
	// ft_free_process(info->path, command);

void	ft_child_process(t_info *info, int i, int *fd)
{
	int		j;
	char	**command;
	char	*cmd_path;

	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (info->infile_error == 1)
		exit(0);
	command = ft_split(info->av[i], ' ');
	j = 0;
	while (info->path[j])
	{
		cmd_path = ft_strjoin(info->path[j], command[0]);
		if (access(cmd_path, X_OK) == 0)
		{
			execve(cmd_path, command, info->env);
			perror("execve");
			free(cmd_path);
			ft_free_process(info->path, command);
		}
		free(cmd_path);
		j++;
	}
	ft_free_process(info->path, command);
}

void	ft_parent_process(t_info *info, int j)
{
	int		i;
	char	**command;
	char	*cmd_path;
	int		outfile;

	outfile = open(info->av[j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	command = ft_split(info->av[j], ' ');
	i = 0;
	while (info->path[i])
	{
		cmd_path = ft_strjoin(info->path[i], command[0]);
		if (access(cmd_path, X_OK) == 0)
		{
			execve(cmd_path, command, info->env);
			perror("execve");
			free(cmd_path);
			ft_free_process(info->path, command);
		}
		free(cmd_path);
		i++;
	}
	ft_free_process(info->path, command);
}

void	ft_change_stdin(char *av)
{
	int	infile;

	infile = open(av, O_RDONLY);
	if (infile < 0)
		return ;
	dup2(infile, STDIN_FILENO);
	close(infile);
}

void	ft_start(int ac, char *av[], char *env[])
{
	int		fd[2];
	pid_t	pid;
	t_info	*info;
	int		i;

	info = ft_check_error(ac, av, env);
	ft_change_stdin(av[1]);
	i = 2;
	while (i < (ac - 2))
	{
		if (pipe(fd) < 0)
			ft_error_pipe(info->path);
		pid = fork();
		if (pid < 0)
			ft_error_fork(info->path);
		if (pid == 0)
			ft_child_process(info, i, fd);
		info->infile_error = 0;
		waitpid(pid, NULL, 0);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		i++;
	}
	ft_parent_process(info, i);
}

int	main(int ac, char *av[], char *env[])
{
	int	i;

	i = 1;
	if (ac != 5)
	{
		ft_printf("format : ./pipex file1 cmd1 cmd2 file2\n");
		return (0);
	}
	while (i != (ac))
	{
		if (av[i][0] == '\0')
		{
			ft_printf("Error: empty argument detected at position %d\n", i);
			return (0);
		}
		i++;
	}
	ft_start(ac, av, env);
	return (0);
}
