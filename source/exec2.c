/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:14:09 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/01 15:15:13 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_builtins(int i, t_command *command, t_envp **envp)
{
	int		fd[2];
	pid_t	pid;

	if (command->next && !command->out_redir)
		pipe(fd);
	if (command->next)
	{
		pid = fork();
		if (pid == 0)
		{
			if (command->next && !command->out_redir)
				ft_redirect_fd(0, fd);
			ft_exec_builtins(i, command, envp);
			exit(0); // a changer
		}
		waitpid(pid, NULL, 0);
		if (command->next && !command->out_redir)
			ft_redirect_fd(1, fd);
	}
	else
		ft_exec_builtins(i, command, envp);
}

void	ft_exec_builtins(int i, t_command *command, t_envp **envp)
{
	if (i == 1)
		ft_echo();
	if (i == 2)
		ft_cd();
	if (i == 3)
		ft_pwd();
	if (i == 4)
		ft_pre_export(envp, command->arg);
	if (i == 5)
		ft_pre_unset(envp, command->arg);
	if (i == 6)
		ft_env(envp);
	if (i == 7)
		ft_exit();
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
	if (ft_isalpha(command->arg[0]) == 1)
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
