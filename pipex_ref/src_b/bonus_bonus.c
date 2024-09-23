/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:53:06 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/04/25 15:56:06 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_get_text(char *av)
{
	char	*buffer;
	char	*lim;
	ssize_t	b_read;
	int		fd[2];

	if (pipe(fd) < 0)
		exit(0);
	buffer = ft_calloc(1024, sizeof(char));
	lim = ft_strjoin(av, "\n");
	b_read = ft_read_buffer(buffer, 0);
	while (ft_strncmp(buffer, lim, b_read) != 0)
	{
		ft_putstr_fd(buffer, fd[1]);
		free(buffer);
		buffer = ft_calloc(1024, sizeof(char));
		b_read = ft_read_buffer(buffer, b_read);
	}
	free(buffer);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
}

void	ft_parent_process_b(t_info *info, int j)
{
	int		i;
	char	**command;
	char	*cmd_path;
	int		outfile;

	outfile = open(info->av[j + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
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

t_info	*ft_check_error_bonus(int ac, char *av[], char *env[])
{
	char	**path;
	t_info	*info;

	if (access(av[ac - 1], F_OK) == 0 && access(av[ac - 1], W_OK) != 0)
	{
		ft_putstr_fd("permission denied: ", 2);
		ft_putstr_fd(av[ac - 1], 2);
		ft_putstr_fd("\n", 2);
		exit(0);
	}
	path = get_path(env);
	info = malloc(sizeof(t_info));
	info->path = path;
	info->av = av;
	info->env = env;
	ft_check_command(3, ac, path, av);
	return (info);
}

void	ft_heredoc(int ac, char **av, char **env)
{
	int		fd[2];
	pid_t	pid;
	t_info	*info;
	int		i;

	info = ft_check_error_bonus(ac, av, env);
	ft_get_text(av[2]);
	i = 3;
	while (i < (ac - 2))
	{
		if (pipe(fd) < 0)
			ft_error_pipe(info->path);
		pid = fork();
		if (pid < 0)
			ft_error_fork(info->path);
		if (pid == 0)
			ft_child_process(info, i, fd);
		waitpid(pid, NULL, 0);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		i++;
	}
	ft_parent_process_b(info, i);
}
