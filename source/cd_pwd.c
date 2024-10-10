/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:14:00 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/10 17:31:15 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char **arg, t_data *data, t_envp **envp)
{
	char	*buffer;

	buffer = getcwd(NULL, 0);
	if (!arg[1])
	{
		ft_putstr_fd("cd: argument required\n", 2);
		data->exit_status = 1;
		return ;
	}
	if (arg[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		data->exit_status = 1;
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
		if (ft_strncmp(tmp->var, "PWD", ft_strlen(tmp->var)) == 0)
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

void	ft_pwd(t_data *data)
{
	char	*buffer;

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
