/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:38:47 by joseluis          #+#    #+#             */
/*   Updated: 2024/10/01 14:18:42 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
commencer par verifier qu'il s'agit pas d'une des 7 commandes faite
s'occuper des pipes et redirection 
fork // regarder pipex 
execve
*/

void	start_exec(t_data *data, t_command **command, t_envp **envp)
{
	t_command	*tmp;
	int			fd[2];

	tmp = *command;
	while (tmp)
	{
		if (tmp->out_redir == true && ft_outredir(tmp->out_path) == 1)
		{
			tmp = tmp->next;
			continue ;
		}
		if (tmp->in_redir == true && ft_inredir(tmp->in_path) == 1)
		{
			tmp = tmp->next;
			continue ;
		}
		if (ft_exec_command(tmp, envp) == 0)
		{
			tmp = tmp->next;
			continue ;
		}
		ft_original_std(data, tmp);
		tmp = tmp->next;
	}
	ft_free_command(command);
}

void	ft_original_std(t_data *data, t_command *command)
{
	if (!command->pipeout && data->base_stdin >= 0) {
		if (dup2(data->base_stdin, STDIN_FILENO) == -1)
		{
			perror("dup2 STDIN");
		}
    }
    if (data->base_stdout >= 0)
	{
		if (dup2(data->base_stdout, STDOUT_FILENO) == -1)
		{
			perror("dup2 STDOUT");
		}
	}
}

void	ft_copy_original_std(t_data *data)
{
	data->base_stdin = dup(STDIN_FILENO);
	if (data->base_stdin == -1)
	{
		perror("dup STDIN");
		exit(EXIT_FAILURE);
    }
	data->base_stdout = dup(STDOUT_FILENO);
	if (data->base_stdout == -1)
	{
		perror("dup STDOUT");
		close(data->base_stdin);
		exit(EXIT_FAILURE);
	}
}

int	ft_exec_command(t_command *command, t_envp **envp)
{
	int	i;

	i = ft_check_command(command, envp);
	if (i == -1)
		return (ft_command_not_found(command, envp));
	if (i >= 1 && i <= 7)
		ft_builtins(i, command, envp);
	if (i == 8)
		ft_base_command(command, envp);
	if (i == 9 || 1 == 10)
		ft_absolute_relative_path(command, envp);
	return (0);
}

void	ft_absolute_relative_path(t_command *command, t_envp **envp)
{
	int		fd[2];
	pid_t	pid;
	char	**env;

	if (command->next && !command->out_redir)
		pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		if (command->next && !command->out_redir)
			ft_redirect_fd(0, fd);
		env = convert_envp(envp);
		execve(command->arg[0], command->arg, env);
		perror("execve");
	}
	waitpid(pid, NULL, 0);
	if (command->next && !command->out_redir)
		ft_redirect_fd(1, fd);
	// manque exit statue
}

void	ft_base_command(t_command *command, t_envp **envp)
{
	int		fd[2];
	pid_t	pid;

	if (command->next && !command->out_redir)
		pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		if (command->next && !command->out_redir)
			ft_redirect_fd(0, fd);
		ft_exec_base_command(command, envp);
	}
	waitpid(pid, NULL, 0);
	if (command->next && !command->out_redir)
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

void	ft_redirect_fd(int i, int *fd)
{
	if (i == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (i == 1)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
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
	if (ft_check_absolute_path(command) == 0)
		return (9);
	if (ft_check_relative_path(command) == 0)
		return (10);
	return (-1);
}

int	check_base_command(t_command *command, t_envp **envp)
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

int	free_path_cmd_return_int(char **path, char *cmd, int value)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
	free(cmd);
	return (value);
}

int	ft_check_absolute_path(t_command *command)
{
	if (access(command->arg[0], X_OK) == 0)
		return (0);
	return (1);
}

char	**ft_get_path(t_envp **envp)
{
	t_envp	*tmp;
	char	**path;

	tmp = *envp;
	while(tmp && ft_strncmp(tmp->var, "PATH", 4) != 0)
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	path = ft_split(tmp->value, ":");
	return (path);

}

int	ft_inredir(t_inpath *inpath)
{
	while (inpath)
	{
		if (inpath->here_doc == true)
		{
			ft_heredoc(inpath);
			inpath = inpath->next;
			continue ;
		}
		if (access(inpath->filename, F_OK) == -1)
		{
			perror(inpath->filename);
			perror(": no such file or directory\n");
			return (1);
		}
		if (access(inpath->filename, R_OK) == -1)
		{
			perror(inpath->filename);
			perror(": Permission denied\n");
			return (1);
		}
		ft_change_stdin(inpath);
		inpath = inpath->next;
	}
	return (0);
}

void	ft_change_stdin(t_inpath *inpath)
{
	int	fd;

	fd = open(inpath->filename, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

int	ft_outredir(t_outpath *outpath)
{
	int	fd;

	while (outpath)
	{
		if (access(outpath->filename, F_OK) != -1)
			if (access(outpath->filename, W_OK) == -1)
			{
				perror(outpath->filename);
				perror(": Permission denied\n");
				return (1);
			}
		if (outpath->append == false)
			fd = open(outpath->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(outpath->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			return (1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		outpath =outpath->next;
	}
	return (0);
}

void	ft_heredoc(t_inpath *inpath)
{
    char    *input;
	char	*buffer;
	int		fd[2];

	buffer = NULL;
	if (pipe(fd) < 0)
	{
		perror("pipe error\n");
		return ;
	}
	while (1)
	{
		input = readline("readline> ");
		if (ft_strncmp(input, inpath->filename, ft_strlen(input)) != 0)
			break;
		buffer = ft_strjoin_gnl(buffer, input);
	}
	if (inpath->next == NULL)
		ft_putstr_fd(buffer, fd[1]);
	close(fd[1]);
	if (inpath->next == NULL)
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	free(buffer);
	free(input);
}
