/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:44:59 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/09/23 14:12:48 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_export(t_envp **envp)
{
	t_envp	*tmp;

	tmp = *envp;
	while (tmp)
	{
		ft_printf("declare -x %s\n", tmp->var);
		tmp = tmp->next;
	}
}

void	ft_pre_export(t_envp **envp, char **args)
{
	int	i;

	i = 1;
	if (args[i] == NULL)
		ft_print_export(envp);
	while (args[i])
	{
		if (ft_isalpha(args[i][0]) == 0)
			ft_printf("error: %s: not a valid identifier", args[i]);
		else
			ft_unset(envp, args[i]);
		i++;
	}
}

void	ft_export(t_envp **envp, char *arg)
{
	t_envp	*tmp;
	int		size_var;

	tmp = *envp;
	while (tmp)
	{
		size_var = strlen_var();
	}
}

void	ft_pre_unset(t_envp **envp, char **args)
{
	int	i;

	i = 1;
	if (args[i] == NULL)
		ft_printf("unset: not enough arguments");
	while (args[i])
	{
		ft_unset(envp, args[i]);
		i++;
	}
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
			free(tmp->var);
			free(tmp);
			return ;
		}
		tmp = tmp->next;
	}
}
