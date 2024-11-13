/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 10:27:09 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/11/12 11:20:35 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **arg, t_data *data)
{
	int	i;
	int	option;

	option = 0;
	if (arg[1] && ft_strncmp(arg[1], "-n", ft_strlen(arg[1])) == 0)
	{
		if (ft_strlen(arg[1]) == 2)
			option = 1;
	}
	else if (arg[1])
		ft_printf("%s", arg[1]);
	if (arg[1] != NULL)
	{
		i = 2;
		while (arg[i])
		{
			if (i == 2 && option == 1)
				ft_printf("%s", arg[i++]);
			else
				ft_printf(" %s", arg[i++]);
		}
	}
	if (!option)
		ft_printf("\n");
	data->exit_status = 0;
}

void	ft_exit(t_command *command, t_data *data)
{
	int	i;

	i = 0;
	if (command->pipein == false && command->pipeout == false)
		ft_putstr_fd("exit\n", 2);
	if (command->arg[1] && command->arg[2])
	{
		ft_putstr_fd("exit: too many arguments", 2);
		data->exit_status = 1;
		return ;
	}
	if (!command->arg[1])
		ft_free_all(data, data->exit_status);
	while (command->arg[1][i])
	{
		if (ft_isdigit(command->arg[1][i]) == 0)
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(command->arg[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			ft_free_all(data, 2);
		}
		i++;
	}
	ft_free_all(data, ft_atoi(command->arg[1]) % 256);
}

void	ft_free_all(t_data *data, int exit_value)
{
	ft_free_envp(data->envp);
	if (data->command != NULL)
		free_command(data->command);
	free(data);
	rl_clear_history();
	exit(exit_value);
}
