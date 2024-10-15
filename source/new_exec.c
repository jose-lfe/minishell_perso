/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:11:21 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/15 15:21:35 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern pid_t	g_glob_pid;


void	waiting_pid(t_data *data)
{
	waitpid(-1, &data->exit_status, 0);
	if (WIFEXITED(data->exit_status))
		data->exit_status = WEXITSTATUS(data->exit_status);
	else if (WIFSIGNALED(data->exit_status))
		data->exit_status = 128 + WTERMSIG(data->exit_status);
}

int	ft_exec_command_bis(t_command *command, t_envp **envp, t_data *data)
{
	int		i;
	char	**env;

	i = ft_check_command(command, envp);
	if (i >= 1 && i <= 7)
	{
		ft_exec_builtins(i, command, envp, data);
		exit(data->exit_status);
	}
	if (i == 8)
		ft_exec_base_command(command, envp);
	if (i == 9 || i == -1)
	{
		env = convert_envp(envp);
		execve(command->arg[0], command->arg, env);
	}
	data->exit_status = 127;
	return (1);
}


void	do_child(t_data *data, t_command *current, t_envp **envp, t_pipe p)
{
	int	error;

	error = 0;
	close(p.fd[1]);
	if (p.pre_fd != 0)
	{
		dup2(p.pre_fd, STDIN_FILENO);
		close(p.pre_fd);
	}
	if (current->next != NULL)
	{
		dup2(p.fd[1],STDOUT_FILENO);
		close(p.fd[1]);
	}		
	if (current->inpath && ft_inredir(current->inpath, p.i, data) == 1)
			error = 1;
	if (current->outpath && ft_outredir(current->outpath, p.i) == 1)
			error = 1;
	if (error == 0 && ft_exec_command_bis(current, envp, data) == 0)
		exit(data->exit_status);
}
void	do_parent(t_command *current, t_pipe p)
{
	if (p.pre_fd != 0)
    	close(p.pre_fd);
    if (current->next != NULL)
		close(p.fd[1]);
	p.pre_fd = p.fd[0];
}
void	exec_with_pipe(t_data *data, t_command **command, t_envp **envp)
{
	t_command	*current;
	t_pipe		p;

	p.pre_fd = 0;
	p.i = 0;
	current = *command;
	while (current != NULL)
	{
		if (current->next != NULL)
			pipe(p.fd);
		g_glob_pid = fork();
		if (g_glob_pid == 0)
			do_child(data, current, envp, p);
		else
			do_parent(current, p);
		current = current->next;
		p.i++;
	}
	while (p.i >= 0)
	{
		waiting_pid(data);
		p.i--;
	}
	free_command(*command);
}


void	start(t_data *data, t_command **command, t_envp **envp)
{
	if ((*command)->next)
		exec_with_pipe(data, command, envp);
	else
		start_exec(data, command, envp);
}	