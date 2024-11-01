/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:30:18 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/11/01 12:52:33 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_command(t_command *command, t_envp **envp)
{
	if (ft_strlen(command->arg[0]) == 0)
		return (-1);
	if (ft_compare(command->arg[0], "echo") == 1)
		return (1);
	if (ft_compare(command->arg[0], "cd") == 1)
		return (2);
	if (ft_compare(command->arg[0], "pwd") == 1)
		return (3);
	if (ft_compare(command->arg[0], "export") == 1)
		return (4);
	if (ft_compare(command->arg[0], "unset") == 1)
		return (5);
	if (ft_compare(command->arg[0], "env") == 1)
		return (6);
	if (ft_compare(command->arg[0], "exit") == 1)
		return (7);
	if (ft_compare(command->arg[0], "exit") == 1)
		return (10);
	if (ft_check_base_command(command, envp) == 0)
		return (8);
	if (ft_check_absolute_relative_path(command) == 0)
		return (9);
	return (-1);
}

int	is_str_alpha_num(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == 1)
			return (0);
		i++;
	}
	return (1);
}

int	ft_check_base_command(t_command *command, t_envp **envp)
{
	char	**path;
	int		i;
	char	*cmd;

	if (is_str_alpha_num(command->arg[0]) == 1)
		return (1);
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
	int	i;

	i = 0;
	while (command->arg[0][i] == '.' || command->arg[0][i] == '/')
		i++;
	if (command->arg[0][i] == '\0')
		return (1);
	if (access(command->arg[0], X_OK) == 0)
		return (0);
	return (1);
}

int	should_ignore_dollar(const char *str, int pos)
{
	int	sq;
	int	i;

	i = 0;
	sq = -1;
	while (i < pos)
	{
		if (str[i] == '\'')
			sq = -sq;
		i++;
	}
	if (sq == 1)
		return (1);
	return (0);
}
