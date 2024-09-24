/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:04:01 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/09/24 15:41:12 by jose-lfe         ###   ########.fr       */
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
	while (str[i++])
		j++;
	res = malloc((j + 1) * sizeof(char));
	if (!res)
		return (NULL);
	j = 0;
	while (str[start])
	{
		res[j] = str[start];
		j++;
		start++;
	}
	res[j] = '\0';
	return (res);
}

int	ft_free_str_and_return_1(char *str)
{
	free(str);
	return (1);	
}
