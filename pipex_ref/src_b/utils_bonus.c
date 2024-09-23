/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:29:54 by joseluis          #+#    #+#             */
/*   Updated: 2024/04/08 14:38:13 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**get_path(char *env[])
{
	int		i;
	char	*string_path;
	char	**path;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	string_path = ft_strdup(env[i] + 5);
	path = ft_split(string_path, ':');
	free(string_path);
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin_gnl(path[i], "/");
		i++;
	}
	return (path);
}

void	ft_free_process(char **path, char **command)
{
	ft_free_path(path);
	ft_free_path(command);
	exit(0);
}

void	ft_free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

void	ft_error_pipe(char **path)
{
	perror("Error creating pipe: ");
	ft_free_path(path);
	exit(1);
}

int	ft_read_buffer(char *buffer, ssize_t b_read)
{
	ft_putstr_fd("pipe heredoc> ", STDERR_FILENO);
	b_read = read(STDIN_FILENO, buffer, (1023));
	return (b_read);
}
