/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 10:27:09 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/09 14:25:17 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **arg, t_data *data)
{
	int	i;
	int	option;

	option = 0;
	if (arg[1] && ft_strncmp(arg[1], "-n", ft_strlen(arg[1])) == 0)
		option = 1;
	else if (arg[1])
		ft_printf("%s", arg[1]);
	i = 2;
	while (arg[i])
	{
		if (i == 2 && option == 1)
			ft_printf("%s", arg[i++]);
		else
			ft_printf(" %s", arg[i++]);
	}
	if (!option)
		ft_printf("\n");
	data->exit_status = 0;
}
/*void	ft_echo(char **arg, t_data *data)
{
	bool	option;
	int		i;

	i = 1;
	option = false;
	if (arg[i] && strcmp(arg[i], "-n") == 0)
	{
		option = true;
		i++;
	}
	while (arg[i])
	{
		if (option)
			i++;
		if (i != 1 && !option)
			printf(" ");
		printf("%s", arg[i]);
		i++;
	}
	if (!option)
		printf("\n");
	data->exit_status = 0;
	return ;
}*/
void	ft_exit(char **arg, t_data *data)
{
	int	i;
	
	i = 0;
	ft_putstr_fd("exit\n", 2);
	if (arg[1] && arg[2])
		{
			ft_putstr_fd("exit: too many arguments", 2);
			data->exit_status = 1;
			return ;
		}
	if (!arg[1])
		ft_free_all(data, data->exit_status);
	while (arg[1][i])
	{
		if (ft_isdigit(arg[1][i]) == 0)
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(arg[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			ft_free_all(data, 1);
		}
		i++;
	}
	ft_free_all(data, ft_atoi(arg[1]));
}

void	ft_free_all(t_data *data, int exit_value)
{
	printf("%i", exit_value);
	free(data);
}
