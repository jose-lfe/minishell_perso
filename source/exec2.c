/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:14:09 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/10 17:33:32 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern pid_t glob_pid;

void	ft_builtins(int i, t_command *command, t_envp **envp, t_data *data)
{
	int		fd[2];

	if (command->next && !command->outpath)
		pipe(fd);
	if (command->next)
	{
		glob_pid = fork();
		if (glob_pid == 0)
		{
			if (command->next && !command->outpath)
				ft_redirect_fd(0, fd);
			ft_exec_builtins(i, command, envp, data);
			exit(0); // a changer
		}
		waitpid(glob_pid, NULL, 0);
		if (command->next && !command->outpath)
			ft_redirect_fd(1, fd);
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
	//if (i == 7)
		//ft_exit();
}

int	ft_command_not_found(t_command *command, t_envp **envp, t_data *data)
{
	t_envp	*tmp;
	bool	path;

	path = true;
	tmp = *envp;
	while (tmp && ft_strncmp(tmp->var, "PATH", 4) != 0)
		tmp = tmp->next;
	if (!tmp)
		path = false;
	if (ft_isalpha(command->arg[0][0]) == 1)
	{
		ft_putstr_fd(command->arg[0], 2);
		if (path)
			ft_putstr_fd(": command not found\n", 2);
		else
			ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
	{
		ft_putstr_fd(command->arg[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	data->exit_status = 127;
	return (1);
}
