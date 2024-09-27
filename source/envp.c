/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:49:27 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/09/27 15:12:05 by jose-lfe         ###   ########.fr       */
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

void	ft_env(t_envp **envp)
{
	t_envp	*tmp;
	int		check;

	tmp = *envp;
	check = 0;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "PATH", ft_strlen(tmp->var)) == 0)
			check = 1;
		tmp = tmp->next;
	}
	if (check == 0)
	{
		perror("env: No such file or directory\n");
		return ;
	}
	while (tmp)
	{
		if (tmp->var && tmp->value)
			ft_printf("%s=%s\n", tmp->var, tmp->value);
		tmp = tmp->next;
	}
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
