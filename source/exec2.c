/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:14:09 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/11/05 12:26:11 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern pid_t	g_glob_pid;

void	ft_builtins(int i, t_command *command, t_envp **envp, t_data *data)
{
	int	fd[2];
	int	status;

	if (command->next && !command->outpath)
		pipe(fd);
	if (command->next)
	{
		g_glob_pid = fork();
		if (g_glob_pid == 0)
		{
			if (command->next && !command->outpath)
				ft_redirect_fd(0, fd);
			ft_exec_builtins(i, command, envp, data);
			exit(data->exit_status);
		}
		waitpid(g_glob_pid, NULL, 0);
		if (command->next && !command->outpath)
			ft_redirect_fd(1, fd);
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
	}
	else
		ft_exec_builtins(i, command, envp, data);
}

void	ft_exec_builtins(int i, t_command *command, t_envp **env, t_data *data)
{
	if (i == 1)
		ft_echo(command->arg, data);
	if (i == 2)
		ft_cd(command->arg, data, env);
	if (i == 3)
		ft_pwd(data);
	if (i == 4)
		ft_pre_export(env, command->arg, data);
	if (i == 5)
		ft_pre_unset(env, command->arg, data);
	if (i == 6)
		ft_env(env, data);
	if (i == 7)
		ft_exit(command, data);
}

void	command_not_found2(t_command *command)
{
	int	i;

	i = 0;
	if (access(command->arg[0], F_OK) == 0)
	{
		if (access(command->arg[0], X_OK) != 0)
		{
			ft_putstr_fd(command->arg[0], 2);
			ft_putstr_fd(": Permission denied\n", 2);
			return ;
		}
	}
	while (command->arg[0][i] == '.' || command->arg[0][i] == '/')
		i++;
	if (command->arg[0][i] == '\0')
	{
		ft_putstr_fd(command->arg[0], 2);
		ft_putstr_fd(": Is a directory\n", 2);
	}
	if (ft_isalnum(command->arg[0][i]) == 1)
	{
		ft_putstr_fd(command->arg[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

int	ft_command_not_found(t_command *command, t_envp **envp, t_data *data)
{
	t_envp	*tmp;
	bool	path;

	path = true;
	tmp = *envp;
	while (tmp && ft_compare(tmp->var, "PATH") == 0)
		tmp = tmp->next;
	if (!tmp)
		path = false;
	if (ft_strlen(command->arg[0]) != 0
		&& (command->arg[0][0] == '.' || command->arg[0][0] == '/'))
		command_not_found2(command);
	else
	{
		if (ft_strlen(command->arg[0]) != 0)
			ft_putstr_fd(command->arg[0], 2);
		if (path)
			ft_putstr_fd(": command not found\n", 2);
		else
			ft_putstr_fd(": No such file or directory\n", 2);
	}
	data->exit_status = 127;
	return (1);
}

void	waiting_pid(t_data *data, t_pipe p, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < p.i)
	{
		waitpid(pids[i], &data->exit_status, 0);
		if (WIFEXITED(data->exit_status))
			data->exit_status = WEXITSTATUS(data->exit_status);
		else if (WIFSIGNALED(data->exit_status))
			data->exit_status = 128 + WTERMSIG(data->exit_status);
		i++;
	}
}
