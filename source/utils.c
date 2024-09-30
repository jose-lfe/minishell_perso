/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:04:01 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/09/30 12:25:18 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_var(char *str)
{
	char	*res;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	res = malloc((i + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char 	*ft_get_value(char *str)
{
	char	*res;
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	start = ++i;
	if (!str[i])
		return (NULL);
	while (str[i++])
		j++;
	res = malloc((j + 1) * sizeof(char));
	if (!res)
		return (NULL);
	j = 0;
	while (str[start])
		res[j++] = str[start++];
	res[j] = '\0';
	return (res);
}

int	ft_free_str_and_return_1(char *str)
{
	free(str);
	return (1);	
}

char	**convert_envp(t_envp **env)
{
	t_envp	*current;
	int		count;
	char	**envp;
	int		i;

	count = 0;
	current = *env;
	while (current)
	{
		count++;
		current = current->next;
	}
	envp = malloc((count + 1) * sizeof(char *));
	if (!envp)
		return (NULL);
	current = *env;
	i = 0;
	while (current)
	{
		envp[i++] = ft_fill_envp(current);
		if (!envp[i - 1])
			return (ft_free_tab(envp));
		current = current->next;
	}
	return (envp);
}

char	*ft_fill_envp(t_envp *current)
{
	int		len;
	char	*res;
	int		i;

	len = ft_strlen(current->var) + ft_strlen(current->value) + 2;
	res = malloc(len * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	len = 0;
	while (current->var[i])
	{
		res[i] = current->var[i];
		i++;
	}
	res[i] = '=';
	i++;
	while (current->value && current->value[len])
	{
		res[i] = current->value[len];
		i++;
		len++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_free_tab(char **envp)
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
