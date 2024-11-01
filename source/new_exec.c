/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:11:21 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/11/01 11:43:57 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern pid_t	g_glob_pid;

int	ft_exec_command_bis(t_command *command, t_envp **envp, t_data *data)
{
	int		i;
	char	**env;

	i = ft_check_command(command, envp);
	if (i == -1)
	{
		ft_command_not_found(command, envp, data);
		data->exit_status = 127;
		exit(data->exit_status);
	}
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
	if (i == 10)
		ft_exec_minishell(command, envp, data);
	return (1);
}

void	do_child(t_data *data, t_command *current, t_envp **envp, t_pipe p)
{
	int	error;

	error = 0;
	if (p.pre_fd != 0 && data->flag == 0)
	{
		dup2(p.pre_fd, STDIN_FILENO);
		close(p.pre_fd);
	}
	if (current->next != NULL)
		dup2(p.fd[1], STDOUT_FILENO);
	close(p.fd[0]);
	close(p.fd[1]);
	if (current->outpath && ft_outredir(current->outpath, p.i) == 1)
		error = 1;
	if (error == 0 && ft_exec_command_bis(current, envp, data) == 0)
		exit(data->exit_status);
}

void	do_parent(t_command *current, t_pipe *p)
{
	if (p->pre_fd != 0)
		close(p->pre_fd);
	if (current->next != NULL)
		close(p->fd[1]);
	p->pre_fd = p->fd[0];
}

void	exec_with_pipe(t_data *data, t_command **command, t_envp **envp)
{
	t_command	*current;
	t_pipe		p;
	pid_t		*pids;

	p.pre_fd = 0;
	p.i = 0;
	current = *command;
	while (current)
	{
		current = current->next;
		p.i++;
	}
	pids = malloc(sizeof(pid_t) * p.i);
	current = *command;
	p.i = 0;
	while (current != NULL)
	{
		pids[p.i] = exec_pipe2(data, current, envp, &p);
		p.i++;
		current = current->next;
	}
	waiting_pid(data, p, pids);
	free(pids);
	free_command(*command);
}

/*
void	exec_with_pipe(t_data *data, t_command **command, t_envp **envp)
{
	t_command	*current;
	t_pipe		p;

	p.pre_fd = 0;
	p.i = 0;
	current = *command;
	p.i = exec_pipe2(data, current, envp, p);
	while (p.i > 0)
	{
		waiting_pid(data);
		p.i--;
	}
	free_command(*command);
}*/

void	start(t_data *data, t_command **command, t_envp **envp)
{
	if (*command)
	{
		do_heredoc(command, data);
		if (data->exit_status == 130)
		{
			free_command(*command);
			return ;
		}
		if ((*command)->next)
		{
			exec_with_pipe(data, command, envp);
			original_std(data);
			data->flag = 0;
		}
		else
		{
			start_exec(data, command, envp);
			data->flag = 0;
		}
	}
	else
		return ;
}
