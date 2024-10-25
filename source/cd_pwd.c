/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:14:00 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/25 11:47:11 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char **arg, t_data *data, t_envp **envp)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (!arg[1])
	{
		data->exit_status = ft_go_home(envp, buffer);
		return ;
	}
	if (arg[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		data->exit_status = 1;
		free(buffer);
		return ;
	}
	if (chdir(arg[1]) != 0)
	{
		perror("cd");
		data->exit_status = 1;
		return ;
	}
	data->exit_status = 0;
	ft_change_old_pwd(buffer, envp);
	free(buffer);
	ft_change_new_pwd(envp);
}

void	ft_change_old_pwd(char *buffer, t_envp **envp)
{
	t_envp	*tmp;

	tmp = *envp;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "OLDPWD", ft_strlen(tmp->var)) == 0)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	free(tmp->value);
	tmp->value = ft_strdup(buffer);
}

void	ft_change_new_pwd(t_envp **envp)
{
	t_envp	*tmp;
	char	*buffer;

	tmp = *envp;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "PWD", ft_strlen(tmp->var)) == 0)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	buffer = getcwd(NULL, 0);
	if (!buffer)
		return ;
	free(tmp->value);
	tmp->value = ft_strdup(buffer);
	free(buffer);
}

void	ft_pwd(char **arg, t_data *data)
{
	char	*buffer;

	if (arg[1])
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		data->exit_status = 1;
		return ;
	}
	buffer = getcwd(NULL, 0);
	if (buffer != NULL)
	{
		printf("%s\n", buffer);
		free(buffer);
		data->exit_status = 0;
	}
	else
	{
		perror("getcwd");
		data->exit_status = 1;
	}
}

int	ft_go_home(t_envp **envp, char *buffer)
{
	t_envp	*tmp;
	int		check;

	tmp = *envp;
	check = 0;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "HOME", ft_strlen(tmp->var)) == 0)
		{
			check = 1;
			break ;
		}
		tmp = tmp->next;
	}
	if (check == 0)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		free(buffer);
		return (1);
	}
	ft_change_old_pwd(buffer, envp);
	free(buffer);
	chdir(tmp->value);
	ft_change_new_pwd(envp);
	return (0);
}
