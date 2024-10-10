/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:04:01 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/10/10 17:35:51 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_free_tab(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
	return (NULL);
}

char	**ft_get_path(t_envp **envp)
{
	t_envp	*tmp;
	char	**path;

	tmp = *envp;
	while (tmp && ft_strncmp(tmp->var, "PATH", 4) != 0)
		tmp = tmp->next;
	if (!tmp)
		return (NULL);
	path = ft_split(tmp->value, ':');
	return (path);
}

int	free_path_cmd_return_int(char **path, char *cmd, int value)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
	if (value == 0)
		free(cmd);
	return (value);
}

void	ft_change_var(t_envp **envp, char *arg, int size_var)
{
	t_envp	*tmp;

	tmp = *envp;
	while (tmp)
	{
		if (ft_strncmp(tmp->var, arg, ft_strlen(tmp->var)) == 0)
			break ;
		tmp = tmp->next;
	}
	free(tmp->value);
	tmp->value = ft_strdup(arg + size_var + 1);
}

int	ft_strlen_var(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (-1);
	return (i);
}
