/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:30:18 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/02 12:32:57 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (ft_check_absolute_relative_path(command) == 0)
		return (9);
	return (-1);
}

int	ft_check_base_command(t_command *command, t_envp **envp)
{
	char	**path;
	int		i;
	char	*cmd;

	path = ft_get_path(envp);
	if (!path)
		return (1);
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin_gnl(path[i], "/");
		i++;
	}
	i = 0;
	while (path[i])
	{
		cmd = ft_strjoin(path[i], command->arg[0]);
		if (access(cmd, X_OK) == 0)
			return (free_path_cmd_return_int(path, cmd, 0));
		free(cmd);
		i++;
	} 
	return (free_path_cmd_return_int(path, cmd, 1));
}

int	ft_check_absolute_relative_path(t_command *command)
{
	if (access(command->arg[0], X_OK) == 0)
		return (0);
	return (1);
}