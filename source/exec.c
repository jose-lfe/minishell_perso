/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:38:47 by joseluis          #+#    #+#             */
/*   Updated: 2024/10/04 14:10:20 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern pid_t glob_pid;

/*
commencer par verifier qu'il s'agit pas d'une des 7 commandes faite
s'occuper des pipes et redirection 
fork // regarder pipex 
execve
*/

void	start_exec(t_data *data, t_command **command, t_envp **envp)
{
	t_command	*tmp;
	int			error;
	int			i;

	i = 0;
	tmp = *command;
	while (tmp)
	{
		error = 0;
		if (tmp->inpath && ft_inredir(tmp->inpath, i) == 1)
			error = 1;
		if (tmp->outpath && ft_outredir(tmp->outpath, i) == 1)
			error = 1;
		if (error == 0 && ft_exec_command(tmp, envp, data) == 0)
		{
			tmp = tmp->next;
			continue ;
		}
		ft_original_std(data, tmp);
		tmp = tmp->next;
		i++;
	}
	free_command(*command);
}

int	ft_exec_command(t_command *command, t_envp **envp, t_data *data)
{
	int	i;

	i = ft_check_command(command, envp);
	if (i == -1)
		return (ft_command_not_found(command, envp));
	if (i >= 1 && i <= 7)
		ft_builtins(i, command, envp, data);
	if (i == 8)
		ft_base_command(command, envp);
	if (i == 9)
		ft_absolute_relative_path(command, envp);
	return (1);
}

void	ft_absolute_relative_path(t_command *command, t_envp **envp)
{
	int		fd[2];
	char	**env;

	if (command->next && !command->outpath)
		pipe(fd);
	glob_pid = fork();
	if (glob_pid == 0)
	{
		if (command->next && !command->outpath)
			ft_redirect_fd(0, fd);
		env = convert_envp(envp);
		execve(command->arg[0], command->arg, env);
		perror("execve");
	}
	waitpid(glob_pid, NULL, 0);
	if (command->next && !command->outpath)
		ft_redirect_fd(1, fd);
	// manque exit statue
}

void	ft_base_command(t_command *command, t_envp **envp)
{
	int		fd[2];

	if (command->next && !command->outpath)
		pipe(fd);
	glob_pid = fork();
	if (glob_pid == 0)
	{
		if (command->next && !command->outpath)
			ft_redirect_fd(0, fd);
		ft_exec_base_command(command, envp);
	}
	waitpid(glob_pid, NULL, 0);
	if (command->next && !command->outpath)
		ft_redirect_fd(1, fd);
	// manque exit statue
}

void	ft_exec_base_command(t_command *command, t_envp **envp)
{
	char	**path;
	char	**env;
	int		i;
	char	*cmd;

	env = convert_envp(envp);
	path = ft_get_path(envp);
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
			execve(cmd, command->arg, env);
		free(cmd);
		i++;
	} 
}
