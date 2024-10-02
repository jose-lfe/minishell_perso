/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:14:00 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/02 12:27:36 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char **arg, t_data *data)
{
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
	}
	else
		data->exit_status = 0;
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
