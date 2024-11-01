/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:49:27 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/31 11:43:44 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envp	*ft_copy_envp(char **env)
{
	int		i;
	t_envp	*start;

	i = 1;
	if (!env[0])
		return (NULL);
	start = ft_new_var(env[0]);
	while (env[i])
	{
		ft_add_back(&start, ft_new_var(env[i]));
		i++;
	}
	return (start);
}

t_envp	*ft_new_var(char *str)
{
	t_envp	*new;

	new = malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	new->var = ft_get_var(str);
	new->value = ft_get_value(str);
	new->pre = NULL;
	new->next = NULL;
	return (new);
}

void	ft_add_back(t_envp **envp, t_envp *new)
{
	t_envp	*tmp;

	if (!*envp)
	{
		*envp = new;
		return ;
	}
	tmp = *envp;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
	new->pre = tmp;
}

void	ft_env(t_envp **envp, t_data *data)
{
	t_envp	*tmp;
	int		check;

	tmp = *envp;
	check = 0;
	while (tmp)
	{
		if (ft_compare(tmp->var, "PATH") == 1)
			check = 1;
		tmp = tmp->next;
	}
	if (check == 0)
	{
		ft_putstr_fd("env: No such file or directory\n", 2);
		data->exit_status = 1;
		return ;
	}
	tmp = *envp;
	while (tmp)
	{
		if (tmp->var && tmp->value)
			ft_printf("%s=%s\n", tmp->var, tmp->value);
		tmp = tmp->next;
	}
	data->exit_status = 0;
}

void	ft_free_envp(t_envp *envp)
{
	t_envp	*tmp;

	while (envp != NULL)
	{
		tmp = envp->next;
		if (envp->var)
			free(envp->var);
		if (envp->value)
			free(envp->value);
		free(envp);
		envp = tmp;
	}
}
