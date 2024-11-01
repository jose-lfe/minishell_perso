/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:14:32 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/31 11:36:06 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern pid_t	g_glob_pid;

void	setup(int ac, char **av, char **env, t_envp **envp)
{
	(void)ac;
	(void)av;
	*envp = ft_copy_envp(env);
	setup_signals();
}

char	**change_shlvl(t_envp **envp)
{
	t_envp	*tmp;
	int		shlvl;

	tmp = *envp;
	while (tmp && ft_compare(tmp->var, "SHLVL") == 0)
		tmp = tmp->next;
	if (tmp)
	{
		shlvl = ft_atoi(tmp->value);
		shlvl++;
		free(tmp->value);
		tmp->value = ft_itoa(shlvl);
		return (convert_envp(envp));
	}
	else
	{
		return (convert_envp(envp));
	}
}

void	ft_exec_minishell(t_command *command, t_envp **envp, t_data *data)
{
	int		fd[2];
	char	**env;

	if (command->next && !command->outpath)
		pipe(fd);
	g_glob_pid = fork();
	if (g_glob_pid == 0)
	{
		if (command->next && !command->outpath)
			ft_redirect_fd(0, fd);
		env = change_shlvl(envp);
		execve(command->arg[0], command->arg, env);
	}
	waitpid(g_glob_pid, &data->exit_status, 0);
	if (command->next && !command->outpath)
		ft_redirect_fd(1, fd);
	if (WIFEXITED(data->exit_status))
		data->exit_status = WEXITSTATUS(data->exit_status);
	else if (WIFSIGNALED(data->exit_status))
		data->exit_status = 128 + WTERMSIG(data->exit_status);
}

int	ft_compare(char *str, char *check)
{
	if(ft_strlen(str) == ft_strlen(check))
	{
		if (ft_strncmp(str, check, ft_strlen(str)) == 0)
			return (1);
	}
	return (0);
}
