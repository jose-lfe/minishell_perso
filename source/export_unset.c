/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:44:59 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/03 18:10:03 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_export(t_envp **envp)
{
	t_envp	*tmp;

	tmp = *envp;
	while (tmp)
	{
		if (tmp->value && tmp->var)
			printf("declare -x %s=\"%s\"\n", tmp->var, tmp->value);
		else if (tmp->var && !tmp->value)
			printf("declare -x %s\n", tmp->var);
		tmp = tmp->next;
	}
}

void	ft_pre_export(t_envp **envp, char **args, t_data *data)
{
	int	i;

	i = 1;
	if (args[i] == NULL)
	{
		ft_print_export(envp);
		data->exit_status = 0;
	}
	while (args[i])
	{
		if (ft_isalpha(args[i][0]) == 0)
		{
			ft_printf("error: %s: not a valid identifier", args[i]);
			data->exit_status = 1;
		}
		else
			ft_export(envp, args[i]);
		i++;
	}
}

void	ft_export(t_envp **envp, char *arg)
{
	t_envp	*tmp;
	int		size_var;

	tmp = *envp;
	size_var = ft_strlen_var(arg);
	while (tmp)
	{
		if (size_var == -1
			&& ft_strncmp(tmp->var, arg, ft_strlen(tmp->var)) == 0)
			return ;
		else if (ft_strncmp(tmp->var, arg, ft_strlen(tmp->var)) == 0)
		{
			ft_change_var(envp, arg, size_var);
			return ;
		}
		tmp = tmp->next;
	}
	ft_add_back(envp, ft_new_var(arg));
}

void	ft_pre_unset(t_envp **envp, char **args, t_data *data)
{
	int	i;

	i = 1;
	if (args[i] == NULL)
	{
		ft_printf("unset: not enough arguments\n");
		data->exit_status = 1;
		return ;
	}
	while (args[i])
	{
		ft_unset(envp, args[i]);
		i++;
	}
	data->exit_status = 0;
}

void	ft_unset(t_envp **envp, char *arg)
{
	t_envp	*tmp;

	tmp = *envp;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, arg, ft_strlen(arg)) == 0)
		{
			if (tmp->pre == NULL)
				*envp = tmp->next;
			else
				tmp->pre->next = tmp->next;
			if (tmp->next != NULL)
				tmp->next->pre = tmp->pre;
			if (tmp->var)
				free(tmp->var);
			if (tmp->value)
				free(tmp->value);
			free(tmp);
			return ;
		}
		tmp = tmp->next;
	}
}
