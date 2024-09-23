/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 14:43:28 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/04/25 15:59:13 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_error(char *command, char **cmd, int i)
{
	ft_printf("command not found: %s\n", cmd[0]);
	free(command);
	ft_free_path(cmd);
	return (i + 1);
}

t_info	*ft_check_error(int ac, char *av[], char *env[])
{
	char	**path;
	t_info	*info;

	if (access(av[1], R_OK) != 0)
		ft_putstr_fd("no such infile or no read permission\n", 2);
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
	if (access(av[1], R_OK) != 0)
		info->infile_error = 1;
	else
		info->infile_error = 0;
	ft_check_command(2, ac, path, av);
	return (info);
}

void	ft_check_command(int i, int ac, char **path, char **av)
{
	int		j;
	char	*command;
	char	**cmd;

	while (i < (ac - 1))
	{
		j = 0;
		cmd = ft_split(av[i], ' ');
		command = ft_strjoin(path[j], cmd[0]);
		while (access(command, X_OK) != 0)
		{
			if (!path[j + 1])
				break ;
			free(command);
			command = ft_strjoin(path[++j], cmd[0]);
		}
		if (access(command, X_OK) != 0)
			i = ft_error(command, cmd, i);
		else
		{
			i++;
			free(command);
			ft_free_path(cmd);
		}
	}
}

void	ft_error_fork(char **path)
{
	perror("Error forking process: ");
	ft_free_path(path);
	exit(1);
}
