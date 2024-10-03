/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:14:09 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/03 16:39:05 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtins(int i, t_command *command, t_envp **envp, t_data *data)
{
	int		fd[2];
	pid_t	pid;

	if (command->next && !command->outpath)
		pipe(fd);
	if (command->next)
	{
		pid = fork();
		if (pid == 0)
		{
			if (command->next && !command->outpath)
				ft_redirect_fd(0, fd);
			ft_exec_builtins(i, command, envp, data);
			exit(0); // a changer
		}
		waitpid(pid, NULL, 0);
		if (command->next && !command->outpath)
			ft_redirect_fd(1, fd);
	}
	else
		ft_exec_builtins(i, command, envp, data);
}

void	ft_exec_builtins(int i, t_command *command, t_envp **env, t_data *data)
{
	//if (i == 1)
		//ft_echo();
	if (i == 2)
		ft_cd(command->arg, data);
	if (i == 3)
		ft_pwd(data);
	if (i == 4)
		ft_pre_export(env, command->arg);
	if (i == 5)
		ft_pre_unset(env, command->arg);
	if (i == 6)
		ft_env(env, data);
	//if (i == 7)
		//ft_exit();
}

int	ft_command_not_found(t_command *command, t_envp **envp)
{
	t_envp	*tmp;
	bool	path;

	path = true;
	tmp = *envp;
	while(tmp && ft_strncmp(tmp->var, "PATH", 4) != 0)
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
	// change exit_status
	return (0);
}
