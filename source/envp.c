/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:49:27 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/09/23 14:12:22 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_copy_envp(char **env, t_envp **envp)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_add_back(envp, ft_new_var(env[i]));
		i++;
	}
}

t_envp	*ft_new_var(char *str)
{
	t_envp	*new;

	new = malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	new->var = ft_strdup(str);
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

void	ft_env(t_envp **envp)
{
	t_envp	*tmp;

	tmp = *envp;
	while (tmp)
	{
		ft_printf("%s\n", tmp->var);
		tmp = tmp->next;
	}
}

void	ft_free_envp(t_envp *envp)
{
	t_envp	*tmp;

	while (envp != NULL)
	{
		tmp = envp->next;
		free(envp->var);
		free(envp);
		envp = tmp;
	}
}
